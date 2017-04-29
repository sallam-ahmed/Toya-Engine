#pragma once
#include "GLM/glm.hpp"
#include <GLFW/glfw3.h>

namespace Toya
{
	namespace CoreDrivers
	{
		class Screen
		{
		public:
			static float ScreenWidth;
			static float ScreenHeight;		
			Screen() = default;
			~Screen();
			static glm::vec2 Screen::GetResoultion();
		};

	}
}

