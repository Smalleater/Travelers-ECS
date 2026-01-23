#ifndef TRA_ECS_COMPONENT_INFO_HPP
#define TRA_ECS_COMPONENT_INFO_HPP

#include "TRA/ecs/chunkColumn.hpp"

namespace tra::ecs
{
	struct ComponentInfo
	{
		size_t m_size;
		size_t m_alignment;
		size_t m_id;

		const char* m_name;
		
		void (*m_moveFunc)(void*, void*);
		void (*m_destroyFunc)(void*);
	};
}

#endif
