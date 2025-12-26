#include "TRA/ecs/entityBuffer.hpp"

#include "TRA/ecs/componentManager.hpp"

namespace tra::ecs
{
	EntityBuffer::EntityBuffer(const std::shared_ptr<ComponentManager>& _componentManager)
	{
		m_componentManager = _componentManager;
	}

	EntityBuffer::EntityBuffer(const std::shared_ptr<ComponentManager>& _componentManager, std::vector<Entity>&& _entities)
	{
		m_componentManager = _componentManager;
		m_entities = std::move(_entities);
	}

	void EntityBuffer::addEntity(const Entity _entity)
	{
		if (_entity.m_id >= m_entities.size())
		{
			m_entities.resize(_entity.m_id + 1, Entity::Null);
		}

		m_entities[_entity.m_id] = _entity;
	}

	void EntityBuffer::removeEntity(const Entity _entity)
	{
		if (_entity.m_id >= m_entities.size())
		{
			return;
		}

		if (m_entities[_entity.m_id] == _entity)
		{
			m_entities[_entity.m_id] = Entity::Null;
		}
	}

	std::vector<Entity> EntityBuffer::getEntities()
	{
		std::vector<Entity> entitiesToReturn;
		entitiesToReturn.reserve(m_entities.size());

		for (auto entity : m_entities)
		{
			if (entity != Entity::Null)
			{
				entitiesToReturn.push_back(entity);
			}
		}

		return m_entities;
	}
}