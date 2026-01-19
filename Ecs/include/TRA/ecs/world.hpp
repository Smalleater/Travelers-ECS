#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include "TRA/errorCode.hpp"

#include "TRA/ecs/entityManager.hpp"
#include "TRA/ecs/archetype.hpp"

namespace tra::ecs
{
	class World
	{
	public:
		TRA_API World();
		~World() = default;

		TRA_API Entity createEntity();
		TRA_API void deleteEntity(Entity _entity);

	private:
		EntityManager m_entityManager;
		std::vector<Archetype> m_archetypes;
	};
}

#endif
