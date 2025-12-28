#ifndef TRA_ECS_COMPONENT_HPP
#define TRA_ECS_COMPONENT_HPP

#include "TRA/ecs/iComponent.hpp"
#include "TRA/ecs/autoRegisterComponent.hpp"

#define TRA_CREATE_COMPONENT(NAME, ...) \
struct NAME : tra::ecs::IComponent \
{ \
	__VA_ARGS__ \
private: \
	static inline tra::ecs::AutoRegisterComponent<NAME> m_registrar{}; \
}; \

#endif
