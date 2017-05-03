#pragma once
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>



namespace Toya
{
	namespace Graphics
	{
		class Window
		{
			static int m_Width, m_Height;
			const char* m_Title;
			GLFWwindow *m_Window;
			static double m_Time;
			static void _sizeCallBack(GLFWwindow* window, int width, int height);
			GLuint vao;
			GLuint vbo;
		public:
			Window(const char* name, int width, int height);
			Window();
			~Window();
			bool Closed() const;
			void Update(void update_function()) const;
			void Clear() const;

			void Close() const
			{
				glfwSetWindowShouldClose(m_Window, 1);
			}

			static Window* Main;
			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }

			inline GLFWwindow* GetWindow() const { return m_Window; }

		private:
			bool _init();
			void _centerWindow() const;
			void _setFullScreen() const;

		};
	}
	typedef Graphics::Window TWindow;
}
