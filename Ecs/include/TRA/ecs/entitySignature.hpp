#ifndef TRA_ECS_ENTITY_SIGNATURE_HPP
#define TRA_ECS_ENTITY_SIGNATURE_HPP

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

		void addComponent(const uint8_t _componentId);
		void removeComponent(const uint8_t _componentId);

		bool hasComponent(const uint8_t _componentId) const;

		void addTag(const uint8_t _tagId);
		void removeTag(const uint8_t _tagId);

		bool hasTag(const uint8_t _tagId) const;
	};

	constexpr EntitySignature NULL_ENTITY_SIGNATURE = EntitySignature{};
}

#endif
