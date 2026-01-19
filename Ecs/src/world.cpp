#include "TRA/ecs/world.hpp"

namespace tra::ecs
{
	World::World()
	{
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);
		Archetype baseArchetype(key);
		m_archetypes.push_back(baseArchetype);
		m_archetypeLookUp[key] = m_archetypes.size() - 1;
	}

	Entity World::createEntity()
	{
		Entity entity = m_entityManager.createEntity();
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);

		m_archetypes[m_archetypeLookUp[key]].addEntity(entity);

		return entity;
	}

	void World::deleteEntity(Entity _entity)
	{
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);

		m_archetypes[m_archetypeLookUp[key]].removeEntity(_entity);
		m_entityManager.deleteEntity(_entity);
	}
}