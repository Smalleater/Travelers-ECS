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

		m_archetypes.at(m_archetypeLookUp.at(key))->addEntity(entity, m_entityManager.getEntityData(entity));

		return entity;
	}

	void World::deleteEntity(const Entity _entity)
	{
		EntityData& entityData = m_entityManager.getEntityData(_entity);
		if (entityData.m_archetype)
		{
			removeEntityFromArchetype(entityData.m_archetype, entityData);
		}
		
		m_entityManager.deleteEntity(_entity);
	}

	Archetype* World::getOrCreateArchetype(const ArchetypeKey _key)
	{
		if (m_archetypeLookUp.find(_key) == m_archetypeLookUp.end())
		{
			std::unique_ptr<Archetype> newArchetype = std::make_unique<Archetype>(_key);
			m_archetypes.push_back(std::move(newArchetype));
			m_archetypeLookUp.insert({ _key, m_archetypes.size() - 1 });
		}

		return m_archetypes.at(m_archetypeLookUp.at(_key)).get();
	}

	void World::copyComponentsToArchetype(Archetype* _srcArch, Archetype* _dstArch, 
		const EntityData& _srcData, const EntityData& _dstData, const EntitySignature& _entitySignature)
	{
		for (size_t i = 0; i < ComponentLibrary::getComponentCount(); i++)
		{
			if (!_entitySignature.hasComponent(i))
			{
				continue;
			}

			const ComponentInfo& moveCompInfo = ComponentLibrary::get(i);

			uint8_t* src = _srcArch->getComponentPtr(_srcData, i);
			uint8_t* dst = _dstArch->getComponentPtr(_dstData, i);

			moveCompInfo.m_moveFunc(dst, src);
		}
	}

	void World::removeEntityFromArchetype(Archetype* _archetype, EntityData& _entityData)
	{
		auto result = _archetype->removeEntity(_entityData);
		if (result)
		{
			EntityData& entityMovedData = m_entityManager.getEntityData(m_entityManager.getEntityById(result.value().first));
			entityMovedData.m_row = result.value().second;
		}
	}
}