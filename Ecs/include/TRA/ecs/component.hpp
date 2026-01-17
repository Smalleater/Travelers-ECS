#ifndef TRA_ECS_COMPONENT_HPP
#define TRA_ECS_COMPONENT_HPP

#include "TRA/ecs/componentId.hpp"

#define TRA_REGISTER_COMPONENT(NAME, ...) \
namespace tra::ecs \
{ \
	struct NAME \
	{ \
		__VA_ARGS__ \
		static uint8_t getId() \
		{ \
			return m_componentId.m_id; \
		} \
	private: \
		static inline ComponentId<NAME> m_componentId{}; \
	}; \
} \

#endif
