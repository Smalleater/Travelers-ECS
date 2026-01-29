#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include <unordered_map>
#include <memory>
#include <functional>

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
			return hasComponentImpl(_entity, componentId);
		}

		template<typename T>
		void addComponent(const Entity _entity, const T& _component)
		{
			const size_t componentId = ComponentLibrary::getComponent<T>().m_id;
			addComponentImpl(_entity, componentId, 
				[&_component](uint8_t* _dst)
				{
					new(_dst) T(_component);
				}
			);
		}

		template<typename T>
		void removeComponent(const Entity _entity)
		{
			const size_t componentId = ComponentLibrary::getComponent<T>().m_id;
			removeComponentImpl(_entity, componentId);
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
			setComponentImpl(_entity, componentId, 
				[&_component](uint8_t* _dst)
				{
					new(_dst) T(_component);
				}
			);
		}

		template<typename T>
		bool hasTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			return hasTagImpl(_entity, tagId);
		}

		template<typename T>
		void addTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			addTagImpl(_entity, tagId);
		}

		template<typename T>
		void removeTag(const Entity _entity)
		{
			const size_t tagId = TagLibrary::getTagId<T>();
			removeTagImpl(_entity, tagId);
		}

	private:
		EntityManager m_entityManager;
		std::vector<std::unique_ptr<Archetype>> m_archetypes;
		std::unordered_map<ArchetypeKey, size_t> m_archetypeLookUp;

		TRA_API bool hasComponentImpl(const Entity _entity, const size_t _componentId);
		TRA_API void addComponentImpl(const Entity _entity, const size_t _componentId, std::function<void(uint8_t*)> _constructor);
		TRA_API void removeComponentImpl(const Entity _entity, const size_t _componentId);
		TRA_API void setComponentImpl(const Entity _entity, const size_t _componentId, std::function<void(uint8_t*)> _constructor);

		TRA_API bool hasTagImpl(const Entity _entity, const size_t _tagId);
		TRA_API void addTagImpl(const Entity _entity, const size_t _tagId);
		TRA_API void removeTagImpl(const Entity _entity, const size_t _tagId);

		Archetype* getOrCreateArchetype(const ArchetypeKey _key);
		void copyComponentsToArchetype(Archetype* _srcArch, Archetype* _dstArch, 
			const EntityData& _srcData, const EntityData& _dstData, const EntitySignature& _entitySignature);
		void removeEntityFromArchetype(Archetype* _archetype, EntityData& _entityData);
	};
}

#endif
