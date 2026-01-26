#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	const ComponentInfo& ComponentLibrary::get(size_t _id)
	{
		return m_components.at(_id);
	}

	const size_t ComponentLibrary::getComponentCount()
	{
		return m_components.size();
	}
}