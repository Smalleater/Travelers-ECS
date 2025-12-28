#include "TRA/ecs/componentFactoryRegistry.hpp"

namespace tra::ecs
{
	void ComponentFactoryRegistry::registerComponentImpl(const std::type_index& _type,
		std::function<std::unique_ptr<ISparseSet>()> _factory)
	{
		getFactories()[_type] = std::move(_factory);
	}

	std::function<std::unique_ptr<ISparseSet>()>
		ComponentFactoryRegistry::getFactory(const std::type_index& _type)
	{
		auto& factories = getFactories();
		auto it = factories.find(_type);
		if (it != factories.end())
		{
			return it->second;
		}

		return nullptr;
	}

	std::unordered_map<std::type_index, std::function<std::unique_ptr<ISparseSet>()>>&
		ComponentFactoryRegistry::getFactories()
	{
		static std::unordered_map<std::type_index, std::function<std::unique_ptr<ISparseSet>()>> factories;
		return factories;
	}
}