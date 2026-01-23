#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	const ComponentInfo& ComponentLibrary::get(size_t _id)
	{
		return m_components[_id];
	}
}