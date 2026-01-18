#ifndef TRA_ECS_CHUNK_COLUMNS_HPP
#define TRA_ECS_CHUNK_COLUMNS_HPP

#include <cstdint>

namespace tra::ecs
{
	struct ChunkColumn
	{
		uint8_t m_componentId;
		uint16_t m_offset;
		uint16_t m_stride;
	};
}

#endif
