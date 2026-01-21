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
		TRA_API void deleteEntity(Entity& _entity);

		TRA_API EntityData getEntityData(Entity _entity);

		template<typename T>
		void addComponent(Entity& _entity, const T& _component)
		{
			const ComponentInfo& componentInfo = ComponentLibrary::get<T>();
			EntitySignature& entitySignature = m_entityManager.getSignature(_entity);

			if (entitySignature.hasComponent(componentInfo.m_id))
			{
				TRA_WARNING_LOG("TRA ECS: Attempted to add a component that the entity already possesses.");
				return;
			}

			entitySignature.addComponent(componentInfo.m_id);

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
			uint8_t* dst = entityData.m_archetype->getComponentPtr<T>(entityData);
			new(dst) T(_component);

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

	private:
		EntityManager m_entityManager;
		std::vector<std::unique_ptr<Archetype>> m_archetypes;
		std::unordered_map<ArchetypeKey, size_t> m_archetypeLookUp;
	};
}

#endif
