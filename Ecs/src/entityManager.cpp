#include "TRA/ecs/entityManager.hpp"

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
				throw("TRA_ECS: Max entities reached");
			}

			id = m_nextFreeId++;

			if (id >= m_entities.size())
			{
				m_entities.resize(id + 1, NULL_ENTITY);
				m_signatures.resize(id + 1, NULL_ENTITY_SIGNATURE);
			}
		}

		m_entities[id] = makeEntity(id, m_entities[id].version());

		return m_entities[id];
	}

	void EntityManager::deleteEntity(Entity _entity)
	{
		if (_entity.id() == NULL_ENTITY.id()
			|| _entity.id() >= m_entities.size())
		{
			return;
		}

		m_entities[_entity.id()] = makeEntity(_entity.id(), _entity.version() + 1);
		m_signatures[_entity.id()] = NULL_ENTITY_SIGNATURE;

		m_freeIds.push_back(_entity.id());
	}
}