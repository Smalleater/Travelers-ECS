#include "TRA/ecs/entitySignature.hpp"

namespace tra::ecs
{
	bool EntitySignature::operator==(const EntitySignature& _other) const
	{
		return m_components == _other.m_components && m_tags == _other.m_tags;
	}

	bool EntitySignature::operator!=(const EntitySignature& _other) const
	{
		return !(*this == _other);
	}

	bool EntitySignature::matchesComponents(const EntitySignature& _signature, const EntitySignature& _required, const EntitySignature& _excluded)
	{
		for (size_t i = 0; i < COMPONENT_BLOCK; i++)
		{
			if ((_signature.m_components[i] & _required.m_components[i]) != _required.m_components[i])
			{
				return false;
			}

			if ((_signature.m_components[i] & _excluded.m_components[i]) != 0)
			{
				return false;
			}
		}

		return true;
	}

	bool matchesTags(const EntitySignature& _signature, const EntitySignature& _required, const EntitySignature& _excluded)
	{
		for (size_t i = 0; i < TAG_BLOCK; i++)
		{
			if ((_signature.m_tags[i] & _required.m_tags[i]) != _required.m_tags[i])
			{
				return false;
			}

			if ((_signature.m_tags[i] & _excluded.m_tags[i]) != 0)
			{
				return false;
			}
		}

		return true;
	}

	void EntitySignature::addComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] |= mask;
	}

	void EntitySignature::removeComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] &= ~mask;
	}

	bool EntitySignature::hasComponent(const size_t _componentId) const
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		return (m_components[block] & mask) != 0;
	}

	void EntitySignature::addTag(const size_t _tagId)
	{
		const size_t block = _tagId >> 6;
		const uint64_t mask = 1ull << (_tagId & 63);

		m_tags[block] |= mask;
	}

	void EntitySignature::removeTag(const size_t _tagId)
	{
		const size_t block = _tagId >> 6;
		const uint64_t mask = 1ull << (_tagId & 63);

		m_tags[block] &= ~mask;
	}

	bool EntitySignature::hasTag(const size_t _tagId) const
	{
		const size_t block = _tagId >> 6;
		const uint64_t mask = 1ull << (_tagId & 63);

		return (m_tags[block] & mask) != 0;
	}


}