#pragma once
#include "Component.hpp"

namespace Toya
{
	namespace Components
	{

		class RenderableComponent : public Component
		{
		public:
			RenderableComponent() {}
			virtual ~RenderableComponent() {};
		};
	}
}
