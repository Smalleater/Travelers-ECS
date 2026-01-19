#include "TRA/ecs/world.hpp"

namespace tra::ecs
{
	World::World()
	{
		Archetype baseArchetype(NULL_ENTITY_SIGNATURE);
		m_archetypes.push_back(baseArchetype);
	}

	Entity World::createEntity()
	{
		Entity entity = m_entityManager.createEntity();
		m_archetypes[0].addEntity(entity);
		return entity;
	}

	void World::deleteEntity(Entity _entity)
	{
		m_archetypes[0].removeEntity(_entity);
		m_entityManager.deleteEntity(_entity);
	}
}