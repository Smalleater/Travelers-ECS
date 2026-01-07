#include "TRA/ecs/componentManager.hpp"

namespace tra::ecs
{
	void ComponentManager::removeAllComponentFromEntity(const Entity& _entity)
	{
		for (auto& [type, sparseSet] : m_sparseSets)
		{
			sparseSet->remove(_entity);
		}

		invalidateCachesForEntity(_entity);
	}

	void ComponentManager::removeAllComponentFromEntities(const std::vector<Entity>& _entities)
	{
		for (auto& [type, sparseSet] : m_sparseSets)
		{
			sparseSet->remove(_entities);
		}

		for (const auto& entity : _entities)
		{
			invalidateCachesForEntity(entity);
		}
	}

	ISparseSet* ComponentManager::getOrCreateComponentSparseSet(const std::type_index& _type)
	{
		auto [it, inserted] = m_sparseSets.try_emplace(_type, nullptr);

		if (inserted)
		{
			auto factory = ComponentFactoryRegistry::getFactory(_type);
			assert(factory != nullptr && "Ecs: Component factory not registered");

			it->second = factory();
		}

		return it->second.get();
	}
}