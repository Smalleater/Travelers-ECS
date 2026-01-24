#include "TRA/ecs/entityManager.hpp"

#include <iostream>

namespace tra::ecs
{
	EntityManager::EntityManager()
		: m_nextFreeId(1)
	{
		m_entities.push_back(NULL_ENTITY);
		m_signatures.push_back(NULL_ENTITY_SIGNATURE);
	}

	Entity EntityManager::createEntity()
	{
		EntityId id;

		if (!m_freeIds.empty())
		{
			id = m_freeIds.back();
			m_freeIds.pop_back();
		}
		else
		{
			if (m_nextFreeId >= MAX_ENTITIES)
			{
				throw std::runtime_error("TRA ECS: Max entities reached.");
			}

			id = m_nextFreeId++;

			if (id >= m_entities.size())
			{
				m_entities.resize(id + 1, NULL_ENTITY);
				m_entitiesData.resize(id + 1);
				m_signatures.resize(id + 1, NULL_ENTITY_SIGNATURE);
			}
		}

		m_entities[id] = makeEntity(id, m_entities[id].version());

		return m_entities[id];
	}

	void EntityManager::deleteEntity(Entity _entity)
	{
		EntityId entityId = _entity.id();

		if (entityId == NULL_ENTITY.id()
			|| entityId >= m_entities.size())
		{
			return;
		}

		m_entities[entityId] = makeEntity(entityId, _entity.version() + 1);
		m_entitiesData[entityId] = EntityData();
		m_signatures[entityId] = NULL_ENTITY_SIGNATURE;

		m_freeIds.push_back(_entity.id());
	}

	Entity& EntityManager::getEntityById(const EntityId _id)
	{
		return m_entities.at(_id);
	}

	EntityData& EntityManager::getEntityData(const Entity _entity)
	{
		return m_entitiesData.at(_entity.id());
	}

	EntitySignature& EntityManager::getSignature(const Entity _entity)
	{
		return m_signatures.at(_entity.id());
	}
}