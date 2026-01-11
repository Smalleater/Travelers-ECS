#ifndef TRA_ECS_COMPONENT_TYPE_ID_HPP
#define TRA_ECS_COMPONENT_TYPE_ID_HPP

namespace tra::ecs
{
	using ComponentTypeID = size_t;

	inline ComponentTypeID getNextComponentTypeID()
	{
		static ComponentTypeID lastID = 0;
		return lastID++;
	}

	template<typename T>
	ComponentTypeID getComponentTypeID()
	{
		static ComponentTypeID id = getNextComponentTypeID();
		return id;
	}
}

#endif
