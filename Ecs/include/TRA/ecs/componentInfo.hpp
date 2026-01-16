#ifndef TRA_ECS_COMPONENT_INFO_HPP
#define TRA_ECS_COMPONENT_INFO_HPP

#include <cstdint>

namespace tra::ecs
{
	struct ComponentInfo
	{
		uint16_t m_size;
		uint8_t m_alignement;
		uint8_t m_typeId;

		const char* m_name;

		void (*m_initFunc)(void*);
		void (*m_copyFunc)(void*);
		void (*m_destroyFunc)(void*);
	};
}

#endif
