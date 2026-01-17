#ifndef TRA_ECS_COMPONENT_INFO_HPP
#define TRA_ECS_COMPONENT_INFO_HPP

#include <cstdint>

namespace tra::ecs
{
	struct ComponentInfo
	{
		uint16_t m_size;
		uint8_t m_alignement;
		uint8_t m_id;

		const char* m_name;
		
		void (*m_destroyFunc)(void*);
		void (*m_moveFunc)(void*, void*);
	};
}

#endif
