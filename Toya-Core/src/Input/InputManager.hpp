
#pragma once
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Graphics/Window.hpp"
#include <map>
#include "../Math/Math.hpp"

namespace Toya
{
	namespace Input
	{
		enum KeyCode
		{
			A = GLFW_KEY_A
			,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
			//Numbers
			Alpha0 = GLFW_KEY_0,
			Alpha1,Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
			//Arrows
			RightArrow = GLFW_KEY_RIGHT,
			LeftArrow,DownArrow,UpArrow,
			//Enough So Far
			Esc = GLFW_KEY_ESCAPE
		};
		enum MouseButton
		{
			LeftMouseButton = GLFW_MOUSE_BUTTON_1,
			RightMouseButton,
			MiddleMouseButton
		};
		enum LockState
		{
			Locked =0,
			Free
		};

		class InputManager
		{
		private:
			static Graphics::Window* m_Window;
			static std::map<int, bool> m_KeyFlags;
			static std::map<int, bool> m_KeyReleaseFlags;
			static std::map<int, bool> m_KeyDownFlags;
			static std::map<int, bool> m_MouseButtonFlags;
			static std::map<int, bool> m_MouseButtonDownFlags;
			static std::map<int, bool> m_MouseButtonUpFlags;

			static double m_MouseX;
			static double m_MouseY;
			static double m_MouseDeltaMultiplier;

			static double m_DeltaX;
			static double m_DeltaY;

			static bool m_CursorLocked;
			static double m_scrollXOffset;
			static double m_scrollYOffset;

			static double m_mouseLastX;
			static double m_mouseLastY;

		public:
			inline static double GetMouseX()
			{
				return m_MouseX;
			}
			inline static double GetMouseY()
			{
				return m_MouseY;
			}
			inline static double GetScrollOffsetX()
			{
				return m_scrollXOffset;
			}
			inline static double GetScrollOffsetY()
			{
				return m_scrollYOffset;
			}
			inline static double GetDeltaX()
			{
				auto tx = m_DeltaX;
				m_DeltaX = 0;
				return tx;
			}
			inline static double GetDeltaY()
			{
				auto ty = m_DeltaY;
				m_DeltaY = 0;
				return ty;
			}
			/////////////////////////////////////////////////////////
		public:
			InputManager(TWindow* activeWindow);
			~InputManager();
			static bool GetKey(KeyCode key);
			static bool GetKeyDown(KeyCode key);
			static bool GetKeyUp(KeyCode key);
			static bool GetMouseButton(MouseButton button);
			static bool GetMouseButtonDown(MouseButton button);
			static bool GetMouseButtonUp(MouseButton button);
			static glm::vec2 GetCursorPosition();
			static void SetCursorLockState(LockState lockState);
		
			static void SetDeltaMultiplier(float mul);
		private:
			bool _init() const;

			#pragma region Input CallBack		
			static void __keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);
			static void __mouseButtonCallBack(GLFWwindow* window, int button, int action ,int mods );
			static void __mouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
			static void __cursorPosCallBack(GLFWwindow* window, double xPos, double yPos);
#pragma endregion
			#pragma region Input Helpers
			static void _centerCursor();
			static bool _isCursorCentered();
			#pragma endregion
		
		};
	}
}