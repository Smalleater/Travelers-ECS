#ifndef TRA_ECS_CHUNK_LAYOUT_HPP
#define TRA_ECS_CHUNK_LAYOUT_HPP

#include <cstdint>
#include <vector>

#include "TRA/ecs/chunkColumn.hpp"

namespace tra::ecs
{
	struct ChunkLayout
	{
		uint16_t m_chunkSize;
		uint32_t m_capacity;

		std::vector<ChunkColumn> m_columns;
	};
}

#endif
