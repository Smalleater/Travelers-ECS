#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	std::vector<ComponentInfo> ComponentLibrary::m_components;
	std::unordered_map<std::type_index, size_t> ComponentLibrary::m_componentLookUp;

	const ComponentInfo& ComponentLibrary::getComponent(size_t _id)
	{
		return m_components.at(_id);
	}

	const size_t ComponentLibrary::getCount()
	{
		return m_components.size();
	}
}