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

	void World::destroyEntity(const Entity _entity)
	{
		EntityData& entityData = m_entityManager.getEntityData(_entity);
		if (entityData.m_archetype)
		{
			removeEntityFromArchetype(entityData.m_archetype, entityData);
		}
		
		m_entityManager.deleteEntity(_entity);
	}

	void World::addSystem(std::unique_ptr<ISystem> _ptr)
	{
		m_systems.push_back(std::move(_ptr));
	}

	void World::updateSystems()
	{
		for (size_t i = 0; i < m_systems.size(); i++)
		{
			m_systems[i]->update(this);
		}
	}

	bool World::hasComponentImpl(const Entity _entity, const size_t _componentId)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		return entitySignature.hasComponent(_componentId);
	}

	void World::addComponentImpl(const Entity _entity, const size_t _componentId, std::function<void(uint8_t*)> _constructor)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		EntitySignature oldSignature = entitySignature;

		if (entitySignature.hasComponent(_componentId))
		{
			throw std::runtime_error("TRA ECS: Attempted to add a component that the entity already possesses.");
		}

		entitySignature.addComponent(_componentId);

		EntityData& entityData = m_entityManager.getEntityData(_entity);
		EntityData oldEntityData = entityData;
		Archetype* oldArchetype = entityData.m_archetype;

		ArchetypeKey key(entitySignature.m_components);
		Archetype* archetype = getOrCreateArchetype(key);

		archetype->addEntity(_entity, entityData);
		uint8_t* dst = archetype->getComponentPtr(entityData, _componentId);
		_constructor(dst);

		copyComponentsToArchetype(oldArchetype, archetype, oldEntityData, entityData, oldSignature);

		if (oldArchetype)
		{
			removeEntityFromArchetype(oldArchetype, oldEntityData);
		}
	}

	void World::removeComponentImpl(const Entity _entity, const size_t _componentId)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		if (!entitySignature.hasComponent(_componentId))
		{
			throw std::runtime_error("TRA ECS: Attempted to remove a component that the entity does not possess.");
		}

		entitySignature.removeComponent(_componentId);

		EntityData& entityData = m_entityManager.getEntityData(_entity);
		EntityData oldEntityData = entityData;
		Archetype* oldArchetype = entityData.m_archetype;

		ArchetypeKey key(entitySignature.m_components);
		Archetype* archetype = getOrCreateArchetype(key);

		archetype->addEntity(_entity, entityData);

		copyComponentsToArchetype(oldArchetype, archetype, oldEntityData, entityData, entitySignature);

		if (oldArchetype)
		{
			removeEntityFromArchetype(oldArchetype, oldEntityData);
		}
	}

	void World::setComponentImpl(const Entity _entity, const size_t _componentId, std::function<void(uint8_t*)> _constructor)
	{
		const EntitySignature& signature = m_entityManager.getSignature(_entity);
		if (!signature.hasComponent(_componentId))
		{
			throw std::runtime_error("TRA ECS: Tried to set a component the entity does not have.");
		}

		EntityData& entityData = m_entityManager.getEntityData(_entity);

		uint8_t* dst = entityData.m_archetype->getComponentPtr(entityData, _componentId);
		_constructor(dst);
	}

	bool World::hasTagImpl(const Entity _entity, const size_t _tagId)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		return entitySignature.hasTag(_tagId);
	}

	void World::addTagImpl(const Entity _entity, const size_t _tagId)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		if (entitySignature.hasTag(_tagId))
		{
			throw std::runtime_error("TRA ECS: Attempted to add a tag that the entity already possesses.");
		}

		entitySignature.addTag(_tagId);
	}

	void World::removeTagImpl(const Entity _entity, const size_t _tagId)
	{
		EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
		if (!entitySignature.hasTag(_tagId))
		{
			throw std::runtime_error("TRA ECS: Attempted to remove a tag that the entity does not possess.");
		}

		entitySignature.removeTag(_tagId);
	}

	Archetype* World::getOrCreateArchetype(const ArchetypeKey _key)
	{
		if (m_archetypeLookUp.find(_key) == m_archetypeLookUp.end())
		{
			std::unique_ptr<Archetype> newArchetype = std::make_unique<Archetype>(_key);
			m_archetypes.push_back(std::move(newArchetype));
			m_archetypeLookUp.insert({ _key, m_archetypes.size() - 1 });

			m_queryArchetypeCache.clear();
		}

		return m_archetypes.at(m_archetypeLookUp.at(_key)).get();
	}

	void World::copyComponentsToArchetype(Archetype* _srcArch, Archetype* _dstArch, 
		const EntityData& _srcData, const EntityData& _dstData, const EntitySignature& _entitySignature)
	{
		for (size_t i = 0; i < ComponentLibrary::getCount(); i++)
		{
			if (!_entitySignature.hasComponent(i))
			{
				continue;
			}

			const ComponentInfo& moveCompInfo = ComponentLibrary::getComponent(i);

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