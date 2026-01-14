#include "TRA/ecs/entityManager.hpp"

namespace tra::ecs
{
	EntityManager::EntityManager()
		: m_nextFreeId(1)
	{
		m_entities.push_back(NULL_ENTITY);
		m_signatures.push_back(NULL_ENTITY_SIGNATURE);
	}
}