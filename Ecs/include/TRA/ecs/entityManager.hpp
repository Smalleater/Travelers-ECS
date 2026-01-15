#ifndef TRA_ECS_ENTITY_MANAGER_HPP
#define TRA_ECS_ENTITY_MANAGER_HPP

#include "TRA/export.hpp"

#include <vector>

#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/entitySignature.hpp"

namespace tra::ecs
{
	class EntityManager
	{
	public:
		TRA_API EntityManager();
		~EntityManager() = default;

		Entity createEntity();
		void deleteEntity(Entity _entity);

	private:
		EntityId m_nextFreeId;

		std::vector<Entity> m_entities;
		std::vector<EntityId> m_freeIds;
		
		std::vector<EntitySignature> m_signatures;
	};
}

#endif
