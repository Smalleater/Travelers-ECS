#ifndef TRA_ECS_COMPONENT_REGISTRY_HPP
#define TRA_ECS_COMPONENT_REGISTRY_HPP

#include <unordered_map>
#include <typeindex>

#include "TRA/ecs/componentTraits.hpp"
#include "TRA/ecs/componentTypeID.hpp"

namespace tra::ecs
{
	struct ComponentInfo
	{
		size_t m_size;
		ComponentTraits m_traits;
	};

	class ComponentRegistry
	{
	public:
		template<typename T>
		static ComponentTypeID registerComponent()
		{
			ComponentTypeID id = getComponentTypeID<T>();
			m_infos[id] = { sizeof(T), makeComponentTraits<T>() };
			return id;
		}

		static const ComponentInfo& get(const ComponentTypeID _id)
		{
			return m_infos.at(_id);
		}

	private:
		static inline std::unordered_map<ComponentTypeID, ComponentInfo> m_infos;
	};
}

#endif
