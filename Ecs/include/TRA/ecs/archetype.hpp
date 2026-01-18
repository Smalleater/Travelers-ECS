#ifndef TRA_ECS_ARCHETYPE_HPP
#define TRA_ECS_ARCHETYPE_HPP

#include "TRA/ecs/chunk.hpp"

namespace tra::ecs
{
	constexpr int MAX_CHUNK_SIZE = 64 * 1024;

	class Archetype
	{
	public:
		Archetype(const std::vector<uint8_t>& _ids);
		~Archetype() = default;

	private:
		std::vector<uint8_t> m_componentIds;
		ChunkLayout m_layout;

		std::vector<Chunk> m_chunks;
		std::vector<uint16_t> freeChunkIndices;

		constexpr uint16_t alignUp(uint16_t _value, uint8_t _alignment)
		{
			return (_value + _alignment - 2) & ~(_alignment - 1);
		}

		ChunkLayout buildChunkLayout();
		Chunk createChunk();
	};
}

#endif
