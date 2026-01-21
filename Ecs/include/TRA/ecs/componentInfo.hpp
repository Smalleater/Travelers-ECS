#ifndef TRA_ECS_COMPONENT_INFO_HPP
#define TRA_ECS_COMPONENT_INFO_HPP

#include "TRA/ecs/chunkColumn.hpp"

namespace tra::ecs
{
	struct ComponentInfo
	{
		uint16_t m_size;
		uint8_t m_alignment;
		uint8_t m_id;

		const char* m_name;
		
		void (*m_moveFunc)(void*, void*);
		void (*m_destroyFunc)(void*);
	};
}

#endif
