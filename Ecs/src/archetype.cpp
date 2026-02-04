#include "TRA/ecs/archetype.hpp"

#include <cassert>
#include <malloc.h>
#include <algorithm>
#include <stdexcept>
#include <cstring>

#include "TRA/ecs/entity.hpp"
#include "TRA/ecs/entityData.hpp"
#include "TRA/ecs/componentLibrary.hpp"

namespace tra::ecs
{
	Archetype::Archetype(const SignatureKey& _signature)
		: m_signatureKey(_signature)
	{
		for (size_t i = 0; i < MAX_COMPONENTS; i++)
		{
			if (m_signatureKey.hasKey(i))
			{
				m_componentIds.push_back(i);
			}
		}

		m_layout = buildChunkLayout();
	}

	SignatureKey Archetype::getSignatureKey()
	{
		return m_signatureKey;
	}

	void Archetype::addEntity(const Entity _entity, EntityData& _entityData)
	{
		if (m_freeChunkIndices.empty())
		{
			m_chunks.push_back(createChunk());
			m_freeChunkIndices.push_back(m_chunks.size() - 1);
		}

		size_t chunkIndex = m_freeChunkIndices.back();
		Chunk& chunk = m_chunks[chunkIndex];

		size_t row = chunk.m_count;
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

		m_entitiesIdCache.clear();
	}

	std::optional<std::pair<EntityId, size_t>> Archetype::removeEntity(EntityData& _entityData)
	{
		size_t chunkindex = _entityData.m_chunkIndex;
		Chunk& chunk = m_chunks[chunkindex];

		size_t deadRow = _entityData.m_row;
		size_t lastRow = chunk.m_count - 1;

		EntityId movedEntityId = 0;

		const ChunkColumn& entityColumn = m_layout.m_columns[0];
		uint32_t* entityIds = reinterpret_cast<uint32_t*>(chunk.m_data + entityColumn.m_offset);

		if (deadRow != lastRow)
		{
			for (size_t i = 0; i < m_layout.m_columns.size(); i++)
			{
				const ChunkColumn& column = m_layout.m_columns[i];

				uint8_t* dst = chunk.m_data + column.m_offset + deadRow * column.m_stride;
				uint8_t* src = chunk.m_data + column.m_offset + lastRow * column.m_stride;

				if (i == 0)
				{
					movedEntityId = entityIds[lastRow];
					memcpy(dst, src, sizeof(uint32_t));
				}
				else
				{
					ComponentLibrary::getComponent(column.m_componentId).m_moveFunc(dst, src);
				}
			}
		}

		entityIds[lastRow] = 0;

		size_t rowToDestroy = (deadRow != lastRow) ? lastRow : deadRow;
		for (size_t i = 1; i < m_layout.m_columns.size(); i++)
		{
			const ChunkColumn& column = m_layout.m_columns[i];

			uint8_t* src = chunk.m_data + column.m_offset + rowToDestroy * column.m_stride;

			if (auto destroyFunc = ComponentLibrary::getComponent(column.m_componentId).m_destroyFunc)
			{
				destroyFunc(src);
			}
		}

		if (_entityData.m_archetype == this)
		{
			_entityData.m_archetype = nullptr;
			_entityData.m_chunkIndex = UINT16_MAX;
			_entityData.m_row = UINT16_MAX;
		}

		--chunk.m_count;

		if (!std::binary_search(m_freeChunkIndices.begin(), m_freeChunkIndices.end(), chunkindex))
		{
			m_freeChunkIndices.push_back(chunkindex);

			std::sort(m_freeChunkIndices.begin(), m_freeChunkIndices.end(),
				[](const size_t _a, const size_t _b)
				{
					return _a < _b;
				}
			);
		}

		m_entitiesIdCache.clear();

		return deadRow != lastRow ? std::make_optional(std::make_pair(movedEntityId, deadRow)) : std::nullopt;
	}

	std::vector<EntityId> Archetype::getEntitiesId()
	{
		if (m_entitiesIdCache.size() == 0)
		{
			std::vector<EntityId> result;
			const ChunkColumn& entityColumn = m_layout.m_columns[0];

			for (auto& chunk : m_chunks)
			{
				uint32_t* entityIds = reinterpret_cast<uint32_t*>(chunk.m_data + entityColumn.m_offset);

				for (size_t i = 0; i < chunk.m_count; ++i)
				{
					result.push_back(entityIds[i]);
				}
			}

			m_entitiesIdCache = std::move(result);
		}

		return m_entitiesIdCache;
	}

	uint8_t* Archetype::getComponentPtr(const EntityData& _entityData, const size_t _componentid)
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

		auto it = std::find(m_componentIds.begin(), m_componentIds.end(), _componentid);
		if (it == m_componentIds.end())
		{
			throw std::runtime_error("TRA ECS: Component not found in this archetype.");
		}

		size_t columnIndex = std::distance(m_componentIds.begin(), it) + 1;
		const ChunkColumn& column = m_layout.m_columns[columnIndex];

		return chunk.m_data + column.m_offset + row * column.m_stride;
	}

	ChunkLayout Archetype::buildChunkLayout()
	{
		ChunkLayout layout{};

		std::vector<const ComponentInfo*> componentsInfo;
		componentsInfo.reserve(m_componentIds.size());

		for (auto id : m_componentIds)
		{
			componentsInfo.push_back(&ComponentLibrary::getComponent(id));
		}

		std::sort(componentsInfo.begin(), componentsInfo.end(),
			[](const ComponentInfo* _a, const ComponentInfo* _b)
			{
				return _a->m_alignment > _b->m_alignment;
			}
		);

		size_t capacity = MAX_CHUNK_SIZE / sizeof(uint32_t);

		while (capacity > 0)
		{
			size_t offset = 0;

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

		size_t offset = 0;

		offset = alignUp(offset, alignof(uint32_t));
		layout.m_columns.push_back(ChunkColumn{ SIZE_MAX, static_cast<uint16_t>(offset), sizeof(uint32_t) });
		offset += capacity * sizeof(uint32_t);

		for (auto id : m_componentIds)
		{
			const ComponentInfo& info = ComponentLibrary::getComponent(id);
			offset = alignUp(offset, info.m_alignment);
			layout.m_columns.push_back(ChunkColumn{ info.m_id, static_cast<uint16_t>(offset), info.m_size });
			offset += capacity * info.m_size;
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

#ifdef _WIN32
		chunk.m_data = static_cast<uint8_t*>(_aligned_malloc(m_layout.m_chunkSize, 64));
#elif defined(__unix__) || defined(__APPLE__)
		chunk.m_data = static_cast<uint8_t*>(aligned_alloc(64, m_layout.m_chunkSize));
#endif

		if (!chunk.m_data) {
			throw std::bad_alloc();
		}

		return chunk;
	}
}