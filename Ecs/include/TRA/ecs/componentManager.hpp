#ifndef TRA_ECS_COMPONENT_MANAGER_HPP
#define TRA_ECS_COMPONENT_MANAGER_HPP

#include <algorithm>
#include <memory>
#include <unordered_set>
#include <typeindex>
#include <utility>

#include "TRA/debugUtils.hpp"
#include "TRA/ecs/sparseSet.hpp"
#include "TRA/ecs/queryKey.hpp"
#include "TRA/ecs/iComponent.hpp"
#include "TRA/ecs/componentFactoryRegistry.hpp"

namespace tra::ecs
{
	class ComponentManager
	{
	public:
		ComponentManager() = default;
		~ComponentManager() = default;

		template<typename Component>
		void addComponentToEntity(const Entity& _entity, Component&& _component)
		{
			SparseSet<Component>* sparseSet = getOrCreateComponentSparseSet<Component>();
			sparseSet->insert(_entity, std::move(_component));
			invalidateCachesForComponent<Component>();
		}

		template<typename Component>
		void removeComponentFromEntity(const Entity& _entity)
		{
			SparseSet<Component>* sparseSet = getOrCreateComponentSparseSet<Component>();
			sparseSet->remove(_entity);
			invalidateCachesForComponent<Component>();
		}

		void removeAllComponentFromEntity(const Entity& _entity);
		void removeAllComponentFromEntities(const std::vector<Entity>& _entities);

		template<typename Component>
		Component& getEntityComponent(const Entity& _entity)
		{
			SparseSet<Component>* sparseSet = getOrCreateComponentSparseSet<Component>();
			return sparseSet->get(_entity);
		}

		template<typename Component>
		bool entityHasComponent(const Entity& _entity)
		{
			SparseSet<Component>* sparseSet = getOrCreateComponentSparseSet<Component>();
			return sparseSet->contains(_entity);
		}

		template<typename... Component>
		std::vector<Entity> queryEntityWith(const std::vector<Entity>& _entities)
		{
			QueryKey queryKey = makeQueryKey<Component...>();
			size_t entitiesHash = hashEntities(_entities);
			QueryWithEntitiesKey cacheKey{ queryKey, entitiesHash };

			auto it = m_entityQueryWithCache.find(cacheKey);
			if (it != m_entityQueryWithCache.end())
			{
				return it->second;
			}

			for (const Entity& entity : _entities)
			{
				m_entityToCacheKeys[entity].insert(cacheKey);
			}

			std::vector<Entity> result;
			result.reserve(_entities.size());
			for (const Entity& entity : _entities)
			{
				bool hasAll = (entityHasComponent<Component>(entity) && ...);
				if (hasAll)
				{
					result.push_back(entity);
				}
			}

			m_entityQueryWithCache[cacheKey] = result;

			return result;
		}

		template<typename... Component>
		std::vector<Entity> queryEntityWithout(const std::vector<Entity>& _entities)
		{
			QueryKey queryKey = makeQueryKey<Component...>();
			size_t entitiesHash = hashEntities(_entities);
			QueryWithEntitiesKey cacheKey{ queryKey, entitiesHash };

			auto it = m_entityQueryWithoutCache.find(cacheKey);
			if (it != m_entityQueryWithoutCache.end())
			{
				return it->second;
			}

			for (const Entity& entity : _entities)
			{
				m_entityToCacheKeys[entity].insert(cacheKey);
			}

			std::vector<Entity> result;
			result.reserve(_entities.size());
			for (const Entity& entity : _entities)
			{
				bool hasNone = (!entityHasComponent<Component>(entity) && ...);
				if (hasNone)
				{
					result.push_back(entity);
				}
			}

			m_entityQueryWithoutCache[cacheKey] = result;

			return result;
		}

	private:
		std::unordered_map<std::type_index, std::shared_ptr<ISparseSet>> m_sparseSets;

		std::unordered_map<QueryWithEntitiesKey, std::vector<Entity>> m_entityQueryWithCache;
		std::unordered_map<QueryWithEntitiesKey, std::vector<Entity>> m_entityQueryWithoutCache;

		std::unordered_map<Entity, std::unordered_set<QueryWithEntitiesKey>> m_entityToCacheKeys;

		template<typename Component>
		SparseSet<Component>* getOrCreateComponentSparseSet()
		{
			static_assert(std::is_base_of<IComponent, Component>::value, "Ecs: Component must derive from IComponent");

			std::type_index type = std::type_index(typeid(Component));
			auto [it, inserted] = m_sparseSets.try_emplace(type, nullptr);

			if (inserted)
			{
				auto factory = ComponentFactoryRegistry::getFactory(type);
				assert(factory != nullptr && "Ecs: Component factory not registered");

				it->second = factory();
			}

			return static_cast<SparseSet<Component>*>(it->second.get());
		}

		ISparseSet* getOrCreateComponentSparseSet(const std::type_index& _type);

		template<typename... Component>
		QueryKey makeQueryKey() const
		{
			std::vector<size_t> hashes = { typeid(Component).hash_code()... };
			std::sort(hashes.begin(), hashes.end());
			return QueryKey{ hashes };
		}

		size_t hashEntities(const std::vector<Entity>& _entities)
		{
			size_t seed = 0;
			for (const Entity& entity : _entities)
			{
				seed ^= std::hash<Entity>()(entity) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}

			return seed;
		}

		template<typename Component>
		void invalidateCachesForComponent()
		{
			size_t componentHash = typeid(Component).hash_code();

			for (auto it = m_entityQueryWithCache.begin(); it != m_entityQueryWithCache.end();)
			{
				const std::vector<size_t>& typeHashes = it->first.m_queryKey.m_typeHashes;
				if (std::find(typeHashes.begin(), typeHashes.end(), componentHash) != typeHashes.end())
				{
					it = m_entityQueryWithCache.erase(it);
				}
				else
				{
					++it;
				}
			}

			for (auto it = m_entityQueryWithoutCache.begin(); it != m_entityQueryWithoutCache.end();)
			{
				const std::vector<size_t>& typeHashes = it->first.m_queryKey.m_typeHashes;
				if (std::find(typeHashes.begin(), typeHashes.end(), componentHash) != typeHashes.end())
				{
					it = m_entityQueryWithoutCache.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		void invalidateCachesForEntity(const Entity& _entity)
		{
			auto it = m_entityToCacheKeys.find(_entity);
			if (it != m_entityToCacheKeys.end())
			{
				for (const auto& cacheKey : it->second)
				{
					m_entityQueryWithCache.erase(cacheKey);
					m_entityQueryWithoutCache.erase(cacheKey);
				}

				m_entityToCacheKeys.erase(it);
			}
		}
	};
}

#endif
