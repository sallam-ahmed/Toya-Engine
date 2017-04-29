#include "Screen.hpp"


namespace Toya
{
	namespace CoreDrivers
	{
		float Screen::ScreenWidth;
		float Screen::ScreenHeight;
		glm::vec2 Screen::GetResoultion()
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			return glm::vec2(mode->width, mode->height);
		}
		Screen::~Screen()
		{
		}
	}
}
