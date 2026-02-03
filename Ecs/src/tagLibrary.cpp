#include "TRA/ecs/tagLibrary.hpp"

namespace tra::ecs
{
	std::unordered_map<std::type_index, size_t> TagLibrary::m_tagtLookUp;
}