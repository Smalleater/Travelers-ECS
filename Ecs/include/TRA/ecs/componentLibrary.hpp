#ifndef TRA_ECS_COMPONENT_LIBRARY_HPP
#define TRA_ECS_COMPONENT_LIBRARY_HPP

#include <vector>

#include "TRA/ecs/componentInfo.hpp"

namespace tra::ecs
{
	class ComponentLibrary
	{
	public:
		template<typename T>
		static uint8_t registerComponent()
		{
			uint8_t typeId = static_cast<uint8_t>(m_components.size());

			ComponentInfo info;
			info.m_size = sizeof(T);
			info.m_alignement = alignof(T);
			info.m_typeId = typeId;
			info.m_name = typeid(T).name();

			if constexpr (!std::is_destructible_v<T>)
			{
				info.m_destroyFunc = [](void* _ptr) { static_cast<T*>(_ptr)->~T(); };
			}

			if constexpr (!std::is_trivially_copyable_v<T>)
			{
				info.m_moveFunc = [](void* _dst, void* _src)
					{
						new(_dst) T(std::move(*static_cast<T*>(_src)));
						static_cast<T*>(_src)->~T();
					};
			}

			m_components.push_back(info);

			return typeId;
		}

	private:
		static inline std::vector<ComponentInfo> m_components;
	};
}

#endif
