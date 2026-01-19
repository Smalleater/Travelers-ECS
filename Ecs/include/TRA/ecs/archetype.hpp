#ifndef TRA_ECS_ARCHETYPE_HPP
#define TRA_ECS_ARCHETYPE_HPP

#include <optional>
#include <utility>

#include "TRA/ecs/chunk.hpp"
#include "TRA/ecs/entitySignature.hpp"
#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/archetypeKey.hpp"

namespace tra::ecs
{
	constexpr int MAX_CHUNK_SIZE = 64 * 1024;

	class Archetype
	{
	public:
		Archetype(const ArchetypeKey& _signature);
		~Archetype() = default;

		void addEntity(Entity& _entity);
		std::optional<std::pair<EntityId, uint16_t>> removeEntity(Entity& _entity);

	private:
		const ArchetypeKey m_archetypeKey;

		std::vector<uint8_t> m_componentIds;
		ChunkLayout m_layout;

		std::vector<Chunk> m_chunks;
		std::vector<uint16_t> m_freeChunkIndices;

		constexpr uint16_t alignUp(uint16_t _value, uint8_t _alignment)
		{
			return (_value + _alignment - 2) & ~(_alignment - 1);
		}

		ChunkLayout buildChunkLayout();
		Chunk createChunk();
	};
}

#endif
