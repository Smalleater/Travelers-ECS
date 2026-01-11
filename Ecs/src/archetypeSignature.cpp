#include "TRA/ecs/archetypeSignature.hpp"

namespace tra::ecs
{
	ArchetypeSignature::ArchetypeSignature(std::vector<std::type_index> _type)
		: m_types(std::move(_type))
	{
		normalize();
	}

	bool ArchetypeSignature::operator==(const ArchetypeSignature& _other) const
	{
		return m_types == _other.m_types;
	}

	bool ArchetypeSignature::operator!=(const ArchetypeSignature& _other) const
	{
		return !(*this == _other);
	}

	void ArchetypeSignature::add(std::type_index _type)
	{
		m_types.push_back(_type);
		normalize();
	}

	void ArchetypeSignature::remove(std::type_index _type)
	{
		auto it = std::remove(m_types.begin(), m_types.end(), _type);
		m_types.erase(it, m_types.end());
	}

	const std::vector<std::type_index>& ArchetypeSignature::getTypes() const
	{
		return m_types;
	}

	bool ArchetypeSignature::contains(std::type_index _type) const
	{
		return std::binary_search(m_types.begin(), m_types.end(), _type, 
			[](const std::type_index& _a, const std::type_index& _b) 
			{
				return _a.hash_code() < _b.hash_code();
			});
	}

	bool ArchetypeSignature::containsAll(const ArchetypeSignature& _other) const
	{
		return std::includes(m_types.begin(), m_types.end(), _other.m_types.begin(), _other.m_types.end(),
			[](const std::type_index& _a, const std::type_index& _b)
			{
				return _a.hash_code() < _b.hash_code();
			});
	}

	bool ArchetypeSignature::containsNone(const ArchetypeSignature& _other) const
	{
		for (const auto& type : _other.m_types)
		{
			if (contains(type))
			{
				return false;
			}
		}

		return true;
	}

	void ArchetypeSignature::normalize()
	{
		std::sort(m_types.begin(), m_types.end(), 
			[](const std::type_index& _a, const std::type_index& _b)
			{
				return _a.hash_code() < _b.hash_code();
			});

		m_types.erase(std::unique(m_types.begin(), m_types.end()), m_types.end());
	}
}