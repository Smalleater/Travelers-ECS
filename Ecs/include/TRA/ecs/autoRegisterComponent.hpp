#ifndef TRA_ECS_AUTO_REGISTER_COMPONENT_HPP
#define TRA_ECS_AUTO_REGISTER_COMPONENT_HPP

#include "TRA/ecs/componentFactoryRegistry.hpp"

namespace tra::ecs
{
    template<typename Component>
    struct AutoRegisterComponent
    {
        AutoRegisterComponent()
        {
            ComponentFactoryRegistry::registerComponent<Component>();
        }
    };
}

#endif
