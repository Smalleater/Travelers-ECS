#include "TRA/ecs/engine.hpp"

#include "TRA/debugUtils.hpp"
#include "TRA/ecs/component.hpp"

namespace tra::ecs
{
	Engine::Engine()
	{
		m_entityManager = std::make_unique<EntityManager>();
		m_systemManager = std::make_unique<SystemManager>();
		m_componentManager = std::make_shared<ComponentManager>();
		m_entityBuffer = std::make_shared<EntityBuffer>(m_componentManager);
	}

	Entity Engine::createEntity()
	{
		assert(m_entityManager != nullptr && "Ecs: EntityManager does not exist");
		Entity newEntity = m_entityManager->createEntity();
		m_entityBuffer->addEntity(newEntity);
		return newEntity;
	}

	void Engine::deleteEntity(Entity _entity)
	{
		if (entityHasComponent<DeleteEntityTag>(_entity))
		{
			return;
		}

		addComponentToEntity<DeleteEntityTag>(_entity, DeleteEntityTag{});
		m_deleteEntityBuffer.push_back(_entity);
	}

	void Engine::beginUpdate()
	{
		assert(m_systemManager != nullptr && "Ecs: SystemManager does not exist");
		m_systemManager->beginUpdate(this);
	}

	void Engine::endUpdate()
	{
		assert(m_systemManager != nullptr && "Ecs: SystemManager does not exist");
		m_systemManager->endUpdate(this);

		assert(m_entityManager != nullptr && "Ecs: EntityManager does not exist");
		m_componentManager->removeAllComponentFromEntities(m_deleteEntityBuffer);

		for (const auto& entity : m_deleteEntityBuffer)
		{
			m_entityBuffer->removeEntity(entity);
			m_entityManager->Delete(entity);
		}

		m_deleteEntityBuffer.clear();
	}

	std::shared_ptr<EntityBuffer> Engine::queryEntity()
	{
		return m_entityBuffer;
	}
}