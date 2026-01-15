#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include "TRA/errorCode.hpp"

#include "TRA/ecs/entityManager.hpp"

namespace tra::ecs
{
	class World
	{
	public:
		World() = default;
		~World() = default;

		TRA_API Entity createEntity();
		TRA_API void deleteEntity(Entity _entity);

	private:
		EntityManager m_entityManager;
	};
}

#endif
