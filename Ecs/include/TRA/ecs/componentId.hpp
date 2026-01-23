#ifndef TRA_ECS_AUTO_REGISTER_COMPONENT_HPP
#define TRA_ECS_AUTO_REGISTER_COMPONENT_HPP

#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	template<typename T>
	struct ComponentId
	{
		ComponentId()
		{
			m_id = ComponentLibrary::registerComponent<T>();
		}

		size_t m_id;
	};
}

#endif
