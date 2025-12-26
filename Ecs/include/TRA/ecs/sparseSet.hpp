#ifndef TRA_ECS_SPARSE_SET_HPP
#define TRA_ECS_SPARSE_SET_HPP

#include <vector>
#include <type_traits>
#include <limits>
#include <unordered_map>
#include <optional>

#include "TRA/debugUtils.hpp"

#include "TRA/ecs/utils.hpp"
#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/iComponent.hpp" 

namespace tra::ecs
{
	struct ISparseSet
	{
		virtual ~ISparseSet() = default;
		virtual void remove(const Entity& _entity) = 0;
	};

	template<typename T>
	class SparseSet : public ISparseSet
	{
	public:
		SparseSet() = default;
		~SparseSet() = default;

		bool contains(const Entity& _entity) const noexcept
		{
			if (_entity.m_id >= m_sparse.size())
			{
				return false;
			}

			size_t index = m_sparse[_entity.m_id];
			return index < m_dense.size() 
				&& m_entities[index] != Entity::Null 
				&& m_entities[index].m_version == _entity.m_version;
		}

		void insert(const Entity& _entity, const T& _value)
		{
			if (_entity.m_id >= m_sparse.size())
			{
				m_sparse.resize(_entity.m_id + 1, N_POS);
			}

			if (contains(_entity))
			{
				m_dense[m_sparse[_entity.m_id]] = _value;
				return;
			}

			size_t index = m_dense.size();
			m_dense.push_back(_value);
			m_entities.push_back(_entity);
			m_sparse[_entity.m_id] = index;
		}

		void remove(const Entity& _entity)
		{
			if (!contains(_entity))
			{
				return;
			}

			size_t index = m_sparse[_entity.m_id];
			size_t last = m_dense.size() - 1;

			if (index != last)
			{
				m_dense[index] = std::move(m_dense[last]);
				m_entities[index] = m_entities[last];
				m_sparse[m_entities[index].m_id] = index;
			}

			m_dense.pop_back();
			m_entities.pop_back();
			m_sparse[_entity.m_id] = N_POS;
		}

		T& get(const Entity& _entity)
		{
			assert(contains(_entity) && "Ecs: SparseSet does not contain the value for the given entity");
			return m_dense[m_sparse[_entity.m_id]];
		}

	private:
		static constexpr size_t N_POS = std::numeric_limits<size_t>::max();

		std::vector<T> m_dense;
		std::vector<Entity> m_entities;
		std::vector<size_t> m_sparse;
	};
}

#endif