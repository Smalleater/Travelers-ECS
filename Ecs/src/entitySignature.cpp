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
}