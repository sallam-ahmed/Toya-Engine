#pragma once
#include "Base/Component.hpp"
#include "../Math/AABB.h"

namespace Toya
{
	namespace Components
	{
		class BoxCollider: public Component
		{
			AABB* m_BoundingBox;
		public:
			BoxCollider() = default;
			void init()
			{
				m_BoundingBox = new AABB(transform);
				Free = true;
			}
			inline AABB * GetBoundingBox() const
			{
				return m_BoundingBox;
			}
			bool Free;
		};
	}
}
