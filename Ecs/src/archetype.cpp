#include "TRA/ecs/archetype.hpp"

#include <iostream>

#include <cassert>
#include <malloc.h>
#include <algorithm>

#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/entityData.hpp"
#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	Archetype::Archetype(const ArchetypeKey& _signature)
		: m_archetypeKey(_signature)
	{
		for (uint8_t i = 0; i < MAX_COMPONENTS; i++)
		{
			if (m_archetypeKey.hasComponent(i))
			{
				m_componentIds.push_back(i);
			}
		}

		m_layout = buildChunkLayout();

		std::cout << "Layout capacity" << m_layout.m_capacity << std::endl;
	}

	void Archetype::addEntity(const Entity _entity, EntityData& _entityData)
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

			memset(dst, 0, column.m_stride);
		}

		_entityData.m_archetype = this;
		_entityData.m_chunkIndex = chunkIndex;
		_entityData.m_row = row;

		++chunk.m_count;

		if (chunk.m_count >= chunk.m_capacity)
		{
			m_freeChunkIndices.pop_back();
		}
	}

	std::optional<std::pair<EntityId, uint16_t>> Archetype::removeEntity(EntityData& _entityData)
	{
		uint16_t chunkindex = _entityData.m_chunkIndex;
		Chunk& chunk = m_chunks[chunkindex];

		uint16_t deadRow = _entityData.m_row;
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

		if (_entityData.m_archetype == this)
		{
			_entityData.m_archetype = nullptr;
			_entityData.m_chunkIndex = UINT16_MAX;
			_entityData.m_row = UINT16_MAX;
		}

		--chunk.m_count;

		m_freeChunkIndices.push_back(chunkindex);

		return deadRow != lastRow ? std::make_optional(std::make_pair(movedEntityId, deadRow)) : std::nullopt;
	}

	ChunkLayout Archetype::buildChunkLayout()
	{
		ChunkLayout layout{};

		std::vector<const ComponentInfo*> componentsInfo;
		componentsInfo.reserve(m_componentIds.size());

		for (auto id : m_componentIds)
		{
			componentsInfo.push_back(&ComponentLibrary::get(id));
		}

		std::sort(componentsInfo.begin(), componentsInfo.end(),
			[](const ComponentInfo* _a, const ComponentInfo* _b)
			{
				return _a->m_alignment > _b->m_alignment;
			}
		);

		uint32_t capacity = MAX_CHUNK_SIZE / sizeof(uint32_t);

		while (capacity > 0)
		{
			uint32_t offset = 0;

			offset = alignUp(offset, alignof(uint32_t));
			offset += capacity * sizeof(uint32_t);

			for (auto* info : componentsInfo)
			{
				offset = alignUp(offset, info->m_alignment);
				offset += capacity * info->m_size;
			}

			if (offset <= MAX_CHUNK_SIZE)
			{
				break;
			}

			--capacity;
		}

		assert(capacity > 0 && "TRA ECS: Invalid archetype chunk capacity.");

		layout.m_capacity = capacity;

		uint32_t offset = 0;

		offset = alignUp(offset, alignof(uint32_t));
		layout.m_columns.push_back(ChunkColumn{ 255, static_cast<uint16_t>(offset), sizeof(uint32_t) });

		offset += capacity * sizeof(uint32_t);

		for (auto* info : componentsInfo)
		{
			offset = alignUp(offset, info->m_alignment);
			layout.m_columns.push_back(ChunkColumn{ info->m_id,static_cast<uint16_t>(offset),info->m_size });
			offset += capacity * info->m_size;
		}

		layout.m_chunkSize = offset;

		assert(layout.m_chunkSize <= MAX_CHUNK_SIZE && "TRA ECS: Chunk size exceeds MAX_CHUNK_SIZE");

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