#include "TRA/ecs/archetype.hpp"

#include <cassert>
#include <malloc.h>

#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	Archetype::Archetype(const EntitySignature& _signature)
		: m_entitySignature(_signature)
	{
		for (uint8_t i = 0; i < MAX_COMPONENTS; i++)
		{
			if (m_entitySignature.m_components.test(i))
			{
				m_componentIds.push_back(i);
			}
		}

		m_layout = buildChunkLayout();
	}

	ChunkLayout Archetype::buildChunkLayout()
	{
		ChunkLayout layout{};

		uint16_t bytesPerEntity = ENTITY_INDEX_BITS;
		uint8_t maxAlignement = alignof(uint32_t);

		for (uint8_t id : m_componentIds)
		{
			const ComponentInfo& info = ComponentLibrary::get(id);
			bytesPerEntity += info.m_size;
			maxAlignement = std::max(maxAlignement, info.m_alignment);
		}

		bytesPerEntity = alignUp(bytesPerEntity, maxAlignement);

		layout.m_capacity = MAX_CHUNK_SIZE / bytesPerEntity;
		assert(layout.m_capacity > 0);

		uint16_t offset = 0;

		offset = alignUp(offset, alignof(uint32_t));
		layout.m_columns.push_back({
			255,
			offset,
			sizeof(uint32_t)
			}
		);

		offset += static_cast<uint16_t>(layout.m_capacity * sizeof(uint32_t));

		for (uint8_t id : m_componentIds)
		{
			const ComponentInfo& info = ComponentLibrary::get(id);

			offset = alignUp(offset, info.m_alignment);

			layout.m_columns.push_back({
				id,
				offset,
				info.m_size
				}
			);

			offset += layout.m_capacity * info.m_size;
		}

		layout.m_chunkSize = offset;
		assert(layout.m_chunkSize <= MAX_CHUNK_SIZE);

		return layout;
	}

	Chunk Archetype::createChunk()
	{
		Chunk chunk;

		chunk.m_capacity = m_layout.m_capacity;
		chunk.m_count = 0;

		chunk.m_data = static_cast<uint8_t*>(_aligned_malloc(m_layout.m_chunkSize, 64));
		if (!chunk.m_data) {
			throw std::bad_alloc();
		}

		return chunk;
	}
}