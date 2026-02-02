#include "TRA/ecs/signatureKey.hpp"

namespace tra::ecs
{
	bool SignatureKey::operator==(const SignatureKey& _other) const
	{
		return m_components == _other.m_components;
	}

	bool SignatureKey::operator!=(const SignatureKey& _other) const
	{
		return !(*this == _other);
	}

	bool SignatureKey::matches(const SignatureKey& _key, const SignatureKey& _required, const SignatureKey& _excluded)
	{
		for (size_t i = 0; i < BLOCK; i++)
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

	void SignatureKey::addComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] |= mask;
	}

	void SignatureKey::removeComponent(const size_t _componentId)
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		m_components[block] &= ~mask;
	}

	bool SignatureKey::hasComponent(const size_t _componentId) const
	{
		const size_t block = _componentId >> 6;
		const uint64_t mask = 1ull << (_componentId & 63);

		return (m_components[block] & mask) != 0;
	}
}