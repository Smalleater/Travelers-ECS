#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include <unordered_map>
#include <memory>

#include "TRA/debugUtils.hpp"

#include "TRA/ecs/entityManager.hpp"
#include "TRA/ecs/archetype.hpp"
#include "TRA/ecs/componentLibrary.hpp"
#include "TRA/ecs/tag.hpp"

namespace tra::ecs
{
	class World
	{
	public:
		TRA_API World();
		~World() = default;

		TRA_API Entity createEntity();
		TRA_API void destroyEntity(const Entity _entity);

		template<typename T>
		bool hasComponent(const Entity _entity)
		{
			const size_t& componentId = ComponentLibrary::getComponent<T>().m_id;
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			return entitySignature.hasComponent(componentId);
		}

		template<typename T>
		void addComponent(const Entity _entity, const T& _component)
		{
			const size_t componentId = ComponentLibrary::getComponent<T>().m_id;
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
			EntitySignature oldSignature = entitySignature;

			if (entitySignature.hasComponent(componentId))
			{
				throw std::runtime_error("TRA ECS: Attempted to add a component that the entity already possesses.");
			}

			entitySignature.addComponent(componentId);

			EntityData& entityData = m_entityManager.getEntityData(_entity);
			EntityData oldEntityData = entityData;
			Archetype* oldArchetype = entityData.m_archetype;

			ArchetypeKey key(entitySignature.m_components);
			Archetype* archetype = getOrCreateArchetype(key);

			archetype->addEntity(_entity, entityData);
			uint8_t* dst = archetype->getComponentPtr(entityData, componentId);
			new(dst) T(_component);

			copyComponentsToArchetype(oldArchetype, archetype, oldEntityData, entityData, oldSignature);

			if (oldArchetype)
			{
				removeEntityFromArchetype(oldArchetype, oldEntityData);
			}
		}

		template<typename T>
		void removeComponent(const Entity _entity)
		{
			const size_t componentId = ComponentLibrary::getComponent<T>().m_id;
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			if (!entitySignature.hasComponent(componentId))
			{
				throw std::runtime_error("TRA ECS: Attempted to remove a component that the entity does not possess.");
			}

			entitySignature.removeComponent(componentId);

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

		template<typename T>
		T& getComponent(const Entity _entity)
		{
			const EntitySignature& signature = m_entityManager.getSignature(_entity);

			if (!signature.hasComponent(ComponentLibrary::get<T>().m_id))
			{
				throw std::runtime_error("TRA ECS: Tried to access a component the entity does not have.");
			}

			EntityData& entityData = m_entityManager.getEntityData(_entity);
			return entityData.m_archetype->getComponent<T>(entityData);
		}

		template<typename T>
		void setComponent(const Entity _entity, const T& _component)
		{
			const size_t componentId = ComponentLibrary::getComponent<T>().m_id;
			const EntitySignature& signature = m_entityManager.getSignature(_entity);

			if (!signature.hasComponent(componentId))
			{
				throw std::runtime_error("TRA ECS: Tried to set a component the entity does not have.");
			}

			EntityData& entityData = m_entityManager.getEntityData(_entity);

			uint8_t* dst = entityData.m_archetype->getComponentPtr(entityData, componentId);
			new(dst) T(_component);
		}

		template<typename T>
		bool hasTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			return entitySignature.hasTag(tagId);
		}

		template<typename T>
		void addTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			if (entitySignature.hasTag(tagId))
			{
				throw std::runtime_error("TRA ECS: Attempted to add a tag that the entity already possesses.");
			}

			entitySignature.addTag(tagId);
		}

		template<typename T>
		void removeTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			if (!entitySignature.hasTag(tagId))
			{
				throw std::runtime_error("TRA ECS: Attempted to remove a tag that the entity does not possess.");
			}

			entitySignature.removeTag(tagId);
		}

	private:
		EntityManager m_entityManager;
		std::vector<std::unique_ptr<Archetype>> m_archetypes;
		std::unordered_map<ArchetypeKey, size_t> m_archetypeLookUp;

		TRA_API Archetype* getOrCreateArchetype(const ArchetypeKey _key);
		TRA_API void copyComponentsToArchetype(Archetype* _srcArch, Archetype* _dstArch, 
			const EntityData& _srcData, const EntityData& _dstData, const EntitySignature& _entitySignature);
		TRA_API void removeEntityFromArchetype(Archetype* _archetype, EntityData& _entityData);
	};
}

#endif
