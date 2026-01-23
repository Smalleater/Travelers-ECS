#ifndef TRA_ECS_ARCHETYPE_KEY_HPP
#define TRA_ECS_ARCHETYPE_KEY_HPP

#include "TRA/ecs/entitySignature.hpp"

namespace tra::ecs
{
	struct ArchetypeKey
	{
		std::array<uint64_t, COMPONENT_BLOCK> m_components{};

		TRA_API ArchetypeKey(const std::array<uint64_t, COMPONENT_BLOCK>& _components);
		~ArchetypeKey() = default;

		TRA_API bool operator==(const ArchetypeKey& _other) const;
		bool operator!=(const ArchetypeKey& _other) const;

		bool hasComponent(const size_t _componentId) const;
	};
}

namespace std
{
	template<>
	struct hash<tra::ecs::ArchetypeKey>
	{
		size_t operator()(const tra::ecs::ArchetypeKey& _key) const
		{
			size_t hash = 0;

			for (size_t i = 0; i < tra::ecs::COMPONENT_BLOCK; i++)
			{
				hash ^= std::hash<uint64_t>{}(_key.m_components[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}

			return hash;
		}
	};
}

#endif
