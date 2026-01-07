#include "TRA/ecs/entityManager.hpp"

#include <limits>

#include "TRA/debugUtils.hpp"

namespace tra::ecs
{
	Entity EntityManager::createEntity()
	{
		if (m_freeEntity.empty())
		{
			EntityId newId = static_cast<EntityId>(m_entities.size());

			if (newId == 0)
			{
				newId = 1;
			}

			if (m_entities.size() < newId)
			{
				m_entities.resize(newId);
			}

			return m_entities.emplace_back(Entity{ newId, 0 });
		}

		EntityId entityId = m_freeEntity.front();
		m_freeEntity.pop();

		return m_entities[entityId];
	}

	void EntityManager::Delete(const Entity& _entity)
	{
		if (_entity.m_id == Entity::Null.m_id)
		{
			return;
		}

		++m_entities[_entity.m_id].m_version;
		m_freeEntity.emplace(_entity.m_id);
	}
}