#ifndef TRA_ECS_COMPONENT_FACTORY_REGISTRY_HPP
#define TRA_ECS_COMPONENT_FACTORY_REGISTRY_HPP

#include <typeindex>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <functional>

#include "TRA/export.hpp"
#include "TRA/ecs/sparseSet.hpp"

namespace tra::ecs
{
	class ComponentFactoryRegistry
	{
	public:
		template<typename Component>
		static void registerComponent()
		{
			std::type_index type = std::type_index(typeid(Component));
			registerComponentImpl(type, []() { return std::make_unique<SparseSet<Component>>(); });
		}

		TRA_API static std::function<std::unique_ptr<ISparseSet>()> getFactory(const std::type_index& _type);

	private:
		TRA_API static std::unordered_map<std::type_index, std::function<std::unique_ptr<ISparseSet>()>>& getFactories();
		TRA_API static void registerComponentImpl(const std::type_index& _type, std::function<std::unique_ptr<ISparseSet>()> _factory);
	};
}

#endif