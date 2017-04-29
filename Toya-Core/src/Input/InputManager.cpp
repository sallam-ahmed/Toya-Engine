#include "InputManager.hpp"
#include "../CoreDrivers/Screen.hpp"

namespace Toya
{
	namespace Input
	{
		std::map<int, bool> InputManager::m_KeyFlags;
		std::map<int, bool> InputManager::m_MouseButtonFlags;
		std::map<int, bool> InputManager::m_MouseButtonDownFlags;
		std::map<int, bool> InputManager::m_MouseButtonUpFlags;
		std::map<int, bool> InputManager::m_KeyReleaseFlags;
		std::map<int, bool> InputManager::m_KeyDownFlags;
		double InputManager::m_MouseX;
		double InputManager::m_MouseY;
		double InputManager::m_MouseDeltaMultiplier = 1.0f;
		double InputManager::m_DeltaX;
		double InputManager::m_DeltaY;
		bool InputManager::m_CursorLocked;
		double InputManager::m_scrollXOffset;
		double InputManager::m_scrollYOffset;
		Graphics::Window* InputManager::m_Window;

		double InputManager::m_mouseLastX;
		 double InputManager::m_mouseLastY;
		InputManager::~InputManager()
		{
		}

		bool InputManager::GetKey(KeyCode key)
		{
			return m_KeyFlags[key] || m_KeyDownFlags[key];
		}

		bool InputManager::GetKeyDown(KeyCode key)
		{
			return m_KeyDownFlags[key] || m_KeyFlags[key];
		}

		bool InputManager::GetKeyUp(KeyCode key)
		{
			return m_KeyReleaseFlags[key];
		}

		bool InputManager::GetMouseButton(MouseButton button)
		{
			return m_MouseButtonFlags[button];
		}

		bool InputManager::GetMouseButtonDown(MouseButton button)
		{
			return m_MouseButtonDownFlags[button];
		}

		bool InputManager::GetMouseButtonUp(MouseButton button)
		{
			return m_MouseButtonUpFlags[button];
		}

		glm::vec2 InputManager::GetCursorPosition()
		{
			return glm::vec2(m_MouseX, m_MouseY);
		}

		void InputManager::SetCursorLockState(LockState lockState)
		{
			switch (lockState)
			{
			case Locked:
				m_CursorLocked = true;
				glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			case Free: 
				m_CursorLocked = false;
				break;
			default: ;
			}
		}
		void InputManager::SetDeltaMultiplier(float mul)
		{
			m_MouseDeltaMultiplier = mul;
		}

		bool InputManager::_init() const
		{
			if (glfwSetKeyCallback(m_Window->GetWindow(), __keyCallBack) != NULL) { return false; }
			if (glfwSetCursorPosCallback(m_Window->GetWindow(), __cursorPosCallBack) != NULL) { return false; }
			if (glfwSetMouseButtonCallback(m_Window->GetWindow(), __mouseButtonCallBack) != NULL) { return false; }
			if (glfwSetScrollCallback(m_Window->GetWindow(), __mouseScrollCallBack) != NULL) { return false; }
			
			glfwSetInputMode(m_Window->GetWindow(), GLFW_STICKY_KEYS, GL_TRUE);
			SetCursorLockState(LockState::Free);
			SetDeltaMultiplier(1.0f);

			m_mouseLastX = CoreDrivers::Screen::ScreenWidth / 2;
			m_mouseLastY = CoreDrivers::Screen::ScreenHeight / 2;
			return true;
		}

		InputManager::InputManager(TWindow* activeWindow)
		{
			m_Window = activeWindow;

			if(!_init())
			{
				fprintf(stderr, "Failed to Initialize Input Manager");
			}
		

		}
		/*******************************************************************************/
		/*CALL BACKS*/
		void InputManager::__keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods)
		{
			m_KeyFlags[key] = action == GLFW_PRESS;
			m_KeyReleaseFlags[key] = action == GLFW_RELEASE;
			m_KeyDownFlags[key] = action == GLFW_REPEAT;

		}

		void InputManager::__mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
		{
			
		}

		void InputManager::__mouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
		{
			m_scrollYOffset = yOffset;
			m_scrollXOffset = xOffset;

		}

		void InputManager::__cursorPosCallBack(GLFWwindow* window, double xPos, double yPos)
		{

			m_MouseX = xPos;
			m_MouseY = /*CoreDrivers::Screen::ScreenHeight - */yPos;

			m_DeltaX = m_MouseX - m_mouseLastX;
			m_DeltaY = m_MouseY - m_mouseLastY;

			m_mouseLastX = m_MouseX;
			m_mouseLastY = m_MouseY;
			//if (!_isCursorCentered()) {
			//	//double movedDistanceX;
			//	//double movedDistanceY;
			//	////  the distance (old position - new position)
			//	//// in other words:  how far is the mouse from the center of the window ? The bigger this value, the more we want to turn.
			//	//// note that the old position (x_old, y_old) is fixed in this application (x_old = WindoSizeWidth/2, y_old = WindowSizeHeight/2)
			//	//movedDistanceX = double(m_Window->GetWidth() / 2 - m_MouseX)*m_MouseDeltaMultiplier;
			//	//movedDistanceY = double(m_Window->GetHeight() / 2 - m_MouseY)*m_MouseDeltaMultiplier;
			//	//// Pass the two distances to the Renderer (our drawings)
			//	//m_DeltaX = movedDistanceX;
			//	//m_DeltaY = movedDistanceY;
			//	//Force the new position of the mouse to be in the middle of the window
			//	if (m_CursorLocked) {
			//		_centerCursor();
			//		
			//	}
			//}
		}
		void InputManager::_centerCursor()
		{
			m_MouseX = m_Window->GetWidth() / 2;
			m_MouseY = m_Window->GetHeight() / 2;
			glfwSetCursorPos(m_Window->GetWindow(), m_MouseX, m_MouseY);
		}
		bool InputManager::_isCursorCentered()
		{
			return (m_MouseX == m_Window->GetHeight() / 2 && m_MouseY == m_Window->GetHeight() / 2);
		}

	}
}

