#ifndef TRA_ECS_ARCHETYPE_KEY_HPP
#define TRA_ECS_ARCHETYPE_KEY_HPP

#include "TRA/export.hpp"

#include <array>

namespace tra::ecs
{
	constexpr size_t MAX_ELEMENTS = 64;
	constexpr size_t BLOCK = (MAX_ELEMENTS + 63) / 64;

	struct SignatureKey
	{
		std::array<uint64_t, BLOCK> m_components{};

		SignatureKey() = default;
		SignatureKey(const Signature& _other) = default;
		~SignatureKey() = default;

		TRA_API bool operator==(const SignatureKey& _other) const;
		bool operator!=(const SignatureKey& _other) const;

		TRA_API static bool matches(const SignatureKey& _key, const SignatureKey& _required, const SignatureKey& _excluded);

		TRA_API void addComponent(const size_t _componentId);
		TRA_API void removeComponent(const size_t _componentId);

		bool hasComponent(const size_t _componentId) const;
	};
}

namespace std
{
	template<>
	struct hash<tra::ecs::SignatureKey>
	{
		size_t operator()(const tra::ecs::SignatureKey& _key) const
		{
			size_t hash = 0;

			for (size_t i = 0; i < tra::ecs::BLOCK; i++)
			{
				hash ^= std::hash<uint64_t>{}(_key.m_components[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}

			return hash;
		}
	};
}

#endif
