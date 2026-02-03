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

	void EntitySignature::addComponent(const size_t _componentId)
	{
		m_components.addKey(_componentId);
	}

	void EntitySignature::removeComponent(const size_t _componentId)
	{
		m_components.removeKey(_componentId);
	}

	bool EntitySignature::hasComponent(const size_t _componentId) const
	{
		return m_components.hasKey(_componentId);
	}

	void EntitySignature::addTag(const size_t _tagId)
	{
		m_tags.addKey(_tagId);
	}

	void EntitySignature::removeTag(const size_t _tagId)
	{
		m_tags.removeKey(_tagId);
	}

	bool EntitySignature::hasTag(const size_t _tagId) const
	{
		return m_tags.hasKey(_tagId);
	}
}