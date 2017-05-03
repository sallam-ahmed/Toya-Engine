#include "Window.hpp"
#include "../CoreDrivers/Time.hpp"
#include "../CoreDrivers/Screen.hpp"
#include "../Components/Camera.hpp"



namespace Toya
{
	namespace Graphics
	{
		int Window::m_Width = -1;
		int Window::m_Height = -1;
		double Window::m_Time = 0;
		Graphics::Window* m_Window;
		Window* Window::Main;
		void Window::_sizeCallBack(GLFWwindow* window, int width, int height)
		{
			m_Width = width;
			m_Height = height;
			CoreDrivers::Screen::ScreenHeight = m_Height;
			CoreDrivers::Screen::ScreenWidth = m_Width;
			glViewport(0, 0, width, height);
			Components::Camera::main->SetProjection();
		}

		Window::Window(const char* name, int width, int height)
		{
			
			m_Title = name;
			m_Width = width;
			m_Height = height;

			GLFWvidmode * vidMode;
			//_centerWindow();
			
			if (!_init())
			{
				glfwTerminate();
			}
			//_setFullScreen();
			CoreDrivers::Screen::ScreenHeight = m_Height;
			CoreDrivers::Screen::ScreenWidth = m_Width;
		
		}
		void Window::_centerWindow() const
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowPos(m_Window, (mode->width - m_Width) / 2, (mode->height - m_Height) / 2);
		}
		void Window::_setFullScreen() const
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			//glfwSetWindowSize(m_Window, (mode->width), (mode->height);
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			CoreDrivers::Screen::ScreenWidth = mode->width;
			CoreDrivers::Screen::ScreenHeight = mode->height;
		}
		Window::Window()
		{
			m_Width = m_Height = -1;
			m_Title = nullptr;
			m_Window = nullptr;
		}


		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::Closed() const
		{
			return (glfwWindowShouldClose(m_Window)==1);
		}

		void Window::Update(void update_function()) const
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
			glMatrixMode(GL_MODELVIEW);
		
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				fprintf(stderr, "Error -> %u\n", error);
				system("pause");
			}
			double currentTime = glfwGetTime(); //get currentTime
			double deltaTime = (currentTime - m_Time) * 1000; //subtract the previous recorded time (mTime value)* 1000 to convert from nanoseconds to seconds.
			m_Time = currentTime;
			CoreDrivers::Time::UpdateTime(deltaTime);
		

			update_function();
		/*	glBindVertexArray(vao);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_LINES, 0, 18);*/
			//Draw Axis
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		}

		bool Window::_init()
		{
			if (!glfwInit())
			{
				fprintf(stderr, "Failed to initialize GLFW");
				return false;
			}
			else
			{
				fprintf(stdout, "Initialized GLFW.\n");
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				glfwTerminate();
				fprintf(stderr, "Failed to create GLFW Window");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowSizeCallback(m_Window, _sizeCallBack);
			fprintf(stdout, "OpenGL Version: %s\n",glGetString(GL_VERSION));
			if (glewInit() != GLEW_OK)
			{
				fprintf(stderr, "Could not initialize GLEW!");
				return false;
			}
			else
			{
				fprintf(stdout, "Initialized GLEW.\n");
			}
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //If requesting an OpenGL version below 3.2, GLFW_OPENGL_ANY_PROFILE
			glewExperimental = true; // Needed for core profile

			// Enable depth test

			glEnable(GL_DEPTH_TEST);

			// Accept fragment if it is closer to the camera than the former one

			glDepthFunc(GL_LESS);
			
			glfwSetTime(0);
			glfwSwapInterval(0);
			Main = this;

			//GLfloat vert[] = {
			//	0.0f,0.0f,0.0f,		1.0f,0.0f,0.0f,
			//	5.0f,0.0f,0.0f,		1.0f,0.0f,0.0f,

			//	0.0f,0.0f,0.0f,		0.0f,1.0f,0.0f,
			//	0.0f,5.0f,0.0f,		0.0f,1.0f,0.0f,

			//	0.0f,0.0f,0.0f,		0.0f,0.0f,1.0f,
			//	0.0f,0.0f,5.0f,		0.0f,0.0f,1.0f,
			//};

			//glGenVertexArrays(1, &vao);
			//
			//glGenVertexArrays(1, &vao);
			//glGenBuffers(1, &vbo);

			//glBindVertexArray(vao);
			//glBindBuffer(GL_ARRAY_BUFFER, vbo);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vert) / sizeof(GLfloat), &vert[0], GL_STATIC_DRAW);
			//glEnableVertexAttribArray(0);
			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0));
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			return true;

		}
	}
}
