#ifndef TRA_ECS_ARCHETYPE_HPP
#define TRA_ECS_ARCHETYPE_HPP

#include <unordered_map>

#include "TRA/ecs/archetypeSignature.hpp"
#include "TRA/ecs/entity.hpp"

namespace tra::ecs
{
	class Archetype
	{
	public:
		Archetype(ArchetypeSignature _signature);
		~Archetype() = default;

	private:
		ArchetypeSignature m_signature;

		std::vector<Entity> m_dense;
		std::vector<size_t> m_sparse;

		std::unordered_map<std::type_index, >
	};
}

#endif
