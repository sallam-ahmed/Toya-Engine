#include "Sprite.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{

			Sprite::Sprite(float x, float y, float width, float height, glm::vec4 color):
				Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), color)
			{

			}
			Sprite::Sprite(const glm::vec3 &pos, const glm::vec2& size, glm::vec4 color) :
				Renderable2D(pos, size, color){}
			Sprite::~Sprite()
			{
			}
		}
	}
}