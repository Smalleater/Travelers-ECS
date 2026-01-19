#ifndef TRA_ECS_COMPONENT_LIBRARY_HPP
#define TRA_ECS_COMPONENT_LIBRARY_HPP

#include "TRA/export.hpp"

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
			uint8_t id = static_cast<uint8_t>(m_components.size());

			ComponentInfo info;
			info.m_size = sizeof(T);
			info.m_alignment = alignof(T);
			info.m_id = id;
			info.m_name = typeid(T).name();

			if constexpr (std::is_default_constructible_v<T>)
			{
				info.m_createFunc = [](void* _ptr) { new(_ptr) T(); };
			}

			if constexpr (!std::is_trivially_copyable_v<T>)
			{
				info.m_moveFunc = [](void* _dst, void* _src)
					{
						new(_dst) T(std::move(*static_cast<T*>(_src)));
						static_cast<T*>(_src)->~T();
					};
			}

			if constexpr (!std::is_destructible_v<T>)
			{
				info.m_destroyFunc = [](void* _ptr) { static_cast<T*>(_ptr)->~T(); };
			}

			m_components.push_back(info);

			return id;
		}

		TRA_API static const ComponentInfo& get(uint8_t _id);

	private:
		TRA_API static inline std::vector<ComponentInfo> m_components;
	};
}

#endif
