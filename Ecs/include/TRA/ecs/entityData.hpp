#ifndef TRA_ECS_ENTITY_DATA_HPP
#define TRA_ECS_ENTITY_DATA_HPP

#include <cstdint>

namespace tra::ecs
{
	class Archetype;

	struct EntityData
	{
		Archetype* m_archetype = nullptr;
		uint16_t m_chunkIndex = UINT16_MAX;
		uint16_t m_row = UINT16_MAX;
	};
}

#endif
