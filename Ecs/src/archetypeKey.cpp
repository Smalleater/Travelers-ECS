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

	bool ArchetypeKey::hasComponent(const size_t _componentId) const
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		return (m_components[block] & mask) != 0;
	}
}