#include "TRA/ecs/archetypeKey.hpp"

namespace tra::ecs
{
	ArchetypeKey::ArchetypeKey(const std::array<uint64_t, COMPONENT_BLOCK>& _components)
		: m_components(_components)
	{

	}

	bool ArchetypeKey::operator==(const ArchetypeKey& _other) const
	{
		return m_components == _other.m_components;
	}

	bool ArchetypeKey::operator!=(const ArchetypeKey& _other) const
	{
		return !(*this == _other);
	}
}