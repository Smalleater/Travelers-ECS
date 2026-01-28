#ifndef TRA_ECS_ENTITY_SIGNATURE_HPP
#define TRA_ECS_ENTITY_SIGNATURE_HPP

#include "TRA/export.hpp"

#include <array>
#include <cstdint>

namespace tra::ecs
{
	constexpr size_t MAX_COMPONENTS = 64;
	constexpr size_t MAX_TAGS = 64;

	constexpr size_t COMPONENT_BLOCK = (MAX_COMPONENTS + 63) / 64;
	constexpr size_t TAG_BLOCK = (MAX_TAGS + 63) / 64;

	struct EntitySignature
	{
		std::array<uint64_t, COMPONENT_BLOCK> m_components{};
		std::array<uint64_t, TAG_BLOCK> m_tags{};

		bool operator==(const EntitySignature& _other) const;
		bool operator!=(const EntitySignature& _other) const;

		static bool matchesComponents(const EntitySignature& _signature, const EntitySignature& _required, const EntitySignature& _excluded);
		static bool matchesTags(const EntitySignature& _signature, const EntitySignature& _required, const EntitySignature& _excluded);

		TRA_API void addComponent(const size_t _componentId);
		TRA_API void removeComponent(const size_t _componentId);

		TRA_API bool hasComponent(const size_t _componentId) const;

		TRA_API void addTag(const size_t _tagId);
		TRA_API void removeTag(const size_t _tagId);

		TRA_API bool hasTag(const size_t _tagId) const;
	};

	constexpr EntitySignature NULL_ENTITY_SIGNATURE = EntitySignature{};
}

#endif
