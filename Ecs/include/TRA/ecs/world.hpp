#ifndef TRA_ECS_WORLD_HPP
#define TRA_ECS_WORLD_HPP

#include "TRA/ecs/entityManager.hpp"

namespace tra::ecs
{
	class World
	{
	public:
		World() = default;
		~World() = default;

	private:
		EntityManager m_entityManager;
	};
}

#endif
