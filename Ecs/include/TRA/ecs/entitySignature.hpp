#ifndef TRA_ECS_ENTITY_SIGNATURE_HPP
#define TRA_ECS_ENTITY_SIGNATURE_HPP

#include <bitset>

namespace tra::ecs
{
	constexpr size_t MAX_COMPONENTS = 64;
	constexpr size_t MAX_TAGS = 64;

	using ComponentMask = std::bitset<MAX_COMPONENTS>;
	using TagMask = std::bitset<MAX_TAGS>;

	struct EntitySignature
	{
		ComponentMask m_components;
		TagMask m_tags;
	};

	constexpr EntitySignature NULL_ENTITY_SIGNATURE = EntitySignature{};
}

#endif
