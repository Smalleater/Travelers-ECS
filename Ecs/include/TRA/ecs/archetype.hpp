#ifndef TRA_ECS_ARCHETYPE_HPP
#define TRA_ECS_ARCHETYPE_HPP

#include <optional>
#include <utility>

#include "TRA/ecs/chunk.hpp"
#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/entityData.hpp"
#include "TRA/ecs/entitySignature.hpp"
#include "TRA/ecs/archetypeKey.hpp"

namespace tra::ecs
{
	constexpr int MAX_CHUNK_SIZE = 64 * 1024;

	class Archetype
	{
	public:
		TRA_API Archetype(const ArchetypeKey& _signature);
		~Archetype() = default;

		TRA_API void addEntity(const Entity _entity, EntityData& _entityData);
		TRA_API std::optional<std::pair<EntityId, size_t>> removeEntity(EntityData& _entityData);

		template<typename T>
		uint8_t* getComponentPtr(EntityData& _entityData)
		{
			if (_entityData.m_chunkIndex >= m_chunks.size())
			{
				throw std::runtime_error("TRA ECS: Invalid chunk for this entity.");
			}

			Chunk& chunk = m_chunks[_entityData.m_chunkIndex];
			if (_entityData.m_row >= chunk.m_count)
			{
				throw std::runtime_error("TRA ECS: Invalid row for this entity.");
			}

			size_t row = _entityData.m_row;
			size_t componentId = ComponentLibrary::get<T>().m_id;

			auto it = std::find(m_componentIds.begin(), m_componentIds.end(), componentId);
			if (it == m_componentIds.end())
			{
				throw std::runtime_error("TRA ECS: Component not found in this archetype.");
			}

			size_t columnIndex = std::distance(m_componentIds.begin(), it);
			const ChunkColumn& column = m_layout.m_columns[columnIndex];

			return chunk.m_data + column.m_offset + row * column.m_stride;
		}

	private:
		const ArchetypeKey m_archetypeKey;

		std::vector<size_t> m_componentIds;
		ChunkLayout m_layout;

		std::vector<Chunk> m_chunks;
		std::vector<size_t> m_freeChunkIndices;

		constexpr size_t alignUp(size_t _value, size_t _alignment)
		{
			return (_value + _alignment - 1) & ~(_alignment - 1);
		}

		ChunkLayout buildChunkLayout();
		Chunk createChunk();
	};
}

#endif
