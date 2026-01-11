#ifndef TRA_ECS_COMPONENT_TRAITS_HPP
#define TRA_ECS_COMPONENT_TRAITS_HPP

#include <type_traits>

namespace tra::ecs
{
	struct ComponentTraits
	{
		using ConstructFn = void(*)(void*);
		using DestructFn = void(*)(void*);
		using MoveFn = void(*)(void*, void*);

		ConstructFn m_construct = nullptr;
		DestructFn m_destruct = nullptr;
		MoveFn m_move = nullptr
	};

	template<typename T>
	ComponentTraits makeComponentTraits()
	{
		ComponentTraits traits{};

		if constexpr (!std::is_trivially_constructible_v<T>)
		{
			traits.m_construct = [](void* _ptr) { new (_ptr) T(); };
		}

		if constexpr (!std::is_trivially_destructible_v<T>)
		{
			traits.m_destruct = [](void* _ptr) { static_cast<T*>(_ptr)->~T(); };
		}

		if constexpr (!std::is_trivially_move_assignable_v<T>)
		{
			traits.m_move = [](void* _dst, void* _src)
				{
					*static_cast<T*>(_dst) = std::move(*static_cast<T*>(_src));
				};
		}

		return traits;
	}
}

#endif
