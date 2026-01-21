#include "TRA/ecs/world.hpp"

namespace tra::ecs
{
	World::World()
	{
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);
		std::unique_ptr<Archetype> baseArchetype = std::make_unique<Archetype>(key);
		m_archetypes.push_back(std::move(baseArchetype));
		m_archetypeLookUp[key] = m_archetypes.size() - 1;
	}

	Entity World::createEntity()
	{
		Entity entity = m_entityManager.createEntity();
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);

		m_archetypes[m_archetypeLookUp[key]]->addEntity(entity, m_entityManager.getEntityData(entity));

		return entity;
	}

	void World::deleteEntity(Entity& _entity)
	{
		ArchetypeKey key(NULL_ENTITY_SIGNATURE.m_components);

		m_archetypes[m_archetypeLookUp[key]]->removeEntity(m_entityManager.getEntityData(_entity));
		m_entityManager.deleteEntity(_entity);
	}

	EntityData World::getEntityData(Entity _entity)
	{
		return m_entityManager.getEntityData(_entity);
	}
}