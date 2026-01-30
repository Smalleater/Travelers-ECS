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

	bool ArchetypeKey::matches(const ArchetypeKey& _key, const ArchetypeKey& _required, const ArchetypeKey& _excluded)
	{
		for (size_t i = 0; i < COMPONENT_BLOCK; i++)
		{
			if ((_key.m_components[i] & _required.m_components[i]) != _required.m_components[i])
			{
				return false;
			}

			if ((_key.m_components[i] & _excluded.m_components[i]) != 0)
			{
				return false;
			}
		}

		return true;
	}

	void ArchetypeKey::addComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] |= mask;
	}

	void ArchetypeKey::removeComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] &= ~mask;
	}

	bool ArchetypeKey::hasComponent(const size_t _componentId) const
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		return (m_components[block] & mask) != 0;
	}
}