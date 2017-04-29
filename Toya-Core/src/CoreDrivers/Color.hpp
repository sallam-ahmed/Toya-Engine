#pragma once
#include <GLM/glm.hpp>
namespace Toya
{
	namespace CoreDrivers
	{
		class Color
		{
			
		public:
			static glm::vec4 Red	;
			static glm::vec4 Green	;
			static glm::vec4 Blue	;
			static glm::vec4 Pink;

			float r, g, b, a;
			glm::vec4 glm_color = glm::vec4(1, 0, 1, 1);
			Color(float r,float g,float b,float a)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
				glm_color = glm::vec4(r, g, b, a);
			}
		};
		glm::vec4 Color::Pink	=	glm::vec4(.5f, 0, 0, 1);
		glm::vec4 Color::Red	=	glm::vec4(1, 0, 0, 1);
		glm::vec4 Color::Green	=	glm::vec4(0, 1, 0, 1);
		glm::vec4 Color::Blue	=	glm::vec4(0, 0, 1, 1);
	}
}
