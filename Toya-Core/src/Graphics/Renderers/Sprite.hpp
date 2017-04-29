#pragma once
#include "Base/Renderable2D.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{
			class Sprite : public Renderable2D
			{
			public:
				Sprite(float x, float y, float width, float height, glm::vec4 color);
				Sprite(const glm::vec3 &pos, const glm::vec2& size, glm::vec4 color);
				~Sprite();
			};


		}
	}
}
