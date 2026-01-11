#ifndef TRA_ECS_ARCHETYPE_SIGNATURE_HPP
#define TRA_ECS_ARCHETYPE_SIGNATURE_HPP

#include <vector>
#include <typeindex>
#include <algorithm>

namespace tra::ecs
{
	class ArchetypeSignature
	{
	public:
		ArchetypeSignature() = default;
		ArchetypeSignature(std::vector<std::type_index> _type);
		~ArchetypeSignature() = default;

		bool operator==(const ArchetypeSignature& _other) const;
		bool operator!=(const ArchetypeSignature& _other) const;

		void add(std::type_index _type);
		void remove(std::type_index _type);

		const std::vector<std::type_index>& getTypes() const;

		bool contains(std::type_index _type) const;
		bool containsAll(const ArchetypeSignature& _other) const;
		bool containsNone(const ArchetypeSignature& _other) const;

	private:
		std::vector<std::type_index> m_types;

		void normalize();
	};
}

#endif
