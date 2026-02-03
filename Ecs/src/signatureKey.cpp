#include "TRA/ecs/signatureKey.hpp"

namespace tra::ecs
{
	bool SignatureKey::operator==(const SignatureKey& _other) const
	{
		return m_keys == _other.m_keys;
	}

	bool SignatureKey::operator!=(const SignatureKey& _other) const
	{
		return !(*this == _other);
	}

	bool SignatureKey::matches(const SignatureKey& _signatureKey, const SignatureKey& _required, const SignatureKey& _excluded)
	{
		for (size_t i = 0; i < BLOCK; i++)
		{
			if ((_signatureKey.m_keys[i] & _required.m_keys[i]) != _required.m_keys[i])
			{
				return false;
			}

			if ((_signatureKey.m_keys[i] & _excluded.m_keys[i]) != 0)
			{
				return false;
			}
		}

		return true;
	}

	void SignatureKey::addKey(const size_t _key)
	{
		const size_t block = _key >> 6;
		const uint64_t mask = 1ull << (_key & 63);

		m_keys[block] |= mask;
	}

	void SignatureKey::removeKey(const size_t _key)
	{
		const size_t block = _key >> 6;
		const uint64_t mask = 1ull << (_key & 63);

		m_keys[block] &= ~mask;
	}

	bool SignatureKey::hasKey(const size_t _key) const
	{
		const size_t block = _key >> 6;
		const uint64_t mask = 1ull << (_key & 63);

		return (m_keys[block] & mask) != 0;
	}
}