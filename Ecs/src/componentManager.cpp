#include "TRA/ecs/componentManager.hpp"

namespace tra::ecs
{
	void ComponentManager::removeAllComponentFromEntity(const Entity& _entity)
	{
		for (auto& [typeHash, sparseSet] : m_sparseSets)
		{
			sparseSet->remove(_entity);
		}

		invalidateCachesForEntity(_entity);
	}
}