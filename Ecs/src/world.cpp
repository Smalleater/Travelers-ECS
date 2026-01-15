#include "TRA/ecs/world.hpp"

namespace tra::ecs
{
	Entity World::createEntity()
	{
		return m_entityManager.createEntity();
	}

	void World::deleteEntity(Entity _entity)
	{
		m_entityManager.deleteEntity(_entity);
	}
}