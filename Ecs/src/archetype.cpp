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
			if (m_entitySignature.hasComponent(i))
			{
				m_componentIds.push_back(i);
			}
		}

		m_layout = buildChunkLayout();
	}

	void Archetype::addEntity(Entity& _entity)
	{
		if (m_freeChunkIndices.empty())
		{
			m_chunks.push_back(createChunk());
			m_freeChunkIndices.push_back(static_cast<uint16_t>(m_chunks.size() - 1));
		}

		uint16_t chunkIndex = m_freeChunkIndices.back();
		Chunk& chunk = m_chunks[chunkIndex];

		uint16_t row = chunk.m_count;
		assert(row < chunk.m_capacity);

		const ChunkColumn& entityColumn = m_layout.m_columns[0];

		uint32_t* entityIds = reinterpret_cast<uint32_t*>(chunk.m_data + entityColumn.m_offset);

		entityIds[row] = _entity.id();

		for (size_t i = 1; i < m_layout.m_columns.size(); i++)
		{
			const ChunkColumn& column = m_layout.m_columns[i];
			uint8_t* dst = chunk.m_data + column.m_offset + row * column.m_stride;

			if (auto createFunc = ComponentLibrary::get(column.m_componentId).m_createFunc)
			{
				createFunc(dst);
			}
			else
			{
				memset(dst, 0, column.m_stride);
			}
		}

		_entity.m_archetype = this;
		_entity.m_chunkIndex = chunkIndex;
		_entity.m_row = row;

		++chunk.m_count;

		if (chunk.m_count >= chunk.m_capacity)
		{
			m_freeChunkIndices.pop_back();
		}
	}

	std::optional<std::pair<EntityId, uint16_t>> Archetype::removeEntity(Entity& _entity)
	{
		uint16_t chunkindex = _entity.m_chunkIndex;
		Chunk& chunk = m_chunks[chunkindex];

		uint16_t deadRow = _entity.m_row;
		uint16_t lastRow = chunk.m_count - 1;

		EntityId movedEntityId = 0;

		if (deadRow != lastRow)
		{
			for (size_t i = 0; i < m_layout.m_columns.size(); i++)
			{
				const ChunkColumn& column = m_layout.m_columns[i];

				uint8_t* dst = chunk.m_data + column.m_offset + deadRow * column.m_stride;
				uint8_t* src = chunk.m_data + column.m_offset + lastRow * column.m_stride;

				if (i == 0)
				{
					movedEntityId = *reinterpret_cast<EntityId*>(src);
					memcpy(dst, src, column.m_stride);
				}
				else if (auto moveFunc = ComponentLibrary::get(column.m_componentId).m_moveFunc)
				{
					moveFunc(dst, src);
				}
				else
				{
					memcpy(dst, src, column.m_stride);
				}
			}
		}
		else
		{
			for (size_t i = 1; i < m_layout.m_columns.size(); i++)
			{
				const ChunkColumn& column = m_layout.m_columns[i];

				uint8_t* src = chunk.m_data + column.m_offset + deadRow * column.m_stride;

				if (auto destroyFunc = ComponentLibrary::get(column.m_componentId).m_destroyFunc)
				{
					destroyFunc(src);
				}
			}
		}

		--chunk.m_count;

		m_freeChunkIndices.push_back(chunkindex);

		return deadRow != lastRow ? std::make_optional(std::make_pair(movedEntityId, deadRow)) : std::nullopt;
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