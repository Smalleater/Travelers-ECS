#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include <unordered_map>
#include <memory>

#include "TRA/debugUtils.hpp"

#include "TRA/ecs/entityManager.hpp"
#include "TRA/ecs/archetype.hpp"
#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	class World
	{
	public:
		TRA_API World();
		~World() = default;

		TRA_API Entity createEntity();
		TRA_API void deleteEntity(const Entity _entity);

		TRA_API EntityData getEntityData(const Entity _entity);

		template<typename T>
		void addComponent(const Entity _entity, const T& _component)
		{
			const ComponentInfo& componentInfo = ComponentLibrary::get<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);
			EntitySignature oldSignature = entitySignature;

			if (entitySignature.hasComponent(componentInfo.m_id))
			{
				TRA_WARNING_LOG("TRA ECS: Attempted to add a component that the entity already possesses.");
				return;
			}

			entitySignature.addComponent(componentInfo.m_id);

			EntityData& entityData = m_entityManager.getEntityData(_entity);
			EntityData oldEntityData = entityData;
			Archetype* oldArchetype = entityData.m_archetype;

			ArchetypeKey key(entitySignature.m_components);
			if (m_archetypeLookUp.find(key) == m_archetypeLookUp.end())
			{
				std::unique_ptr<Archetype> newArchetype = std::make_unique<Archetype>(key);
				m_archetypes.push_back(std::move(newArchetype));
				m_archetypeLookUp[key] = m_archetypes.size() - 1;
			}

			m_archetypes.at(m_archetypeLookUp[key])->addEntity(_entity, entityData);
			uint8_t* dst = entityData.m_archetype->getComponentPtr(entityData, componentInfo.m_id);
			new(dst) T(_component);

			for (size_t i = 0; i < ComponentLibrary::getComponentCount(); i++)
			{
				if (!oldSignature.hasComponent(i))
				{
					continue;
				}

				const ComponentInfo& moveCompInfo = ComponentLibrary::get(i);

				uint8_t* src = oldArchetype->getComponentPtr(oldEntityData, i);
				uint8_t* dst = m_archetypes.at(m_archetypeLookUp[key])->getComponentPtr(entityData, i);

				moveCompInfo.m_moveFunc(dst, src);
			}

			if (oldArchetype) 
			{
				auto result = oldArchetype->removeEntity(oldEntityData);
				if (result)
				{
					EntityData& entityMovedData = m_entityManager.getEntityData(m_entityManager.getEntityById(result.value().first));
					entityMovedData.m_row = result.value().second;
				}
			}
		}

		template<typename T>
		void removeComponent(const Entity _entity)
		{
			const ComponentInfo& componentInfo = ComponentLibrary::get<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			if (!entitySignature.hasComponent(componentInfo.m_id))
			{
				TRA_WARNING_LOG("TRA ECS: Attempted to remove a component that the entity does not possess.");
				return;
			}

			entitySignature.removeComponent(componentInfo.m_id);

			EntityData& entityData = m_entityManager.getEntityData(_entity);
			Archetype* oldArchetype = entityData.m_archetype;

			ArchetypeKey key(entitySignature.m_components);
			if (m_archetypeLookUp.find(key) == m_archetypeLookUp.end())
			{
				std::unique_ptr<Archetype> newArchetype = std::make_unique<Archetype>(key);
				m_archetypes.push_back(std::move(newArchetype));
				m_archetypeLookUp[key] = m_archetypes.size() - 1;
			}

			m_archetypes.at(m_archetypeLookUp[key])->addEntity(_entity, entityData);

			if (oldArchetype)
			{
				auto result = oldArchetype->removeEntity(entityData);
				if (result)
				{
					EntityData& entityMovedData = m_entityManager.getEntityData(m_entityManager.getEntityById(result.value().first));
					entityMovedData.m_row = result.value().second;
				}
			}
		}

		template<typename T>
		T& getComponent(const Entity _entity)
		{
			EntitySignature& signature = m_entityManager.getSignature(_entity);

			if (!signature.hasComponent(ComponentLibrary::get<T>().m_id))
			{
				throw std::runtime_error("TRA ECS: Tried to access a component the entity does not have.");
			}

			EntityData& entityData = m_entityManager.getEntityData(_entity);
			return entityData.m_archetype->getComponent<T>(entityData);
		}

	private:
		EntityManager m_entityManager;
		std::vector<std::unique_ptr<Archetype>> m_archetypes;
		std::unordered_map<ArchetypeKey, size_t> m_archetypeLookUp;
	};
}

#endif
