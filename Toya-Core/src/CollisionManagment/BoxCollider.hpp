#pragma once
#include "../Components/Base/Component.hpp"
#include <GLM/detail/type_vec3.hpp>

namespace Toya
{
	namespace Components
	{
		class BoxCollider : public Component
		{
		public:
			glm::vec3 Center;

		private:
			void _updateBoundingBox()
			{
				
			}
		};
	}
}
