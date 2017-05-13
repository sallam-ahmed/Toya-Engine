#pragma once
#include "../PlayerBehaviour.hpp"
#include "../../Components/Camera.hpp"

namespace GamePlay
{
	using namespace Toya::Input;
	using namespace Toya::Components;
	using namespace Toya::CoreDrivers;
	class FPSCamera : public Behaviour
	{
		const GLfloat SENSTIVITY = 1.5f;
		Camera* m_Camera;
		GLfloat m_xOffset, m_yOffset;
	public:

		GLfloat xSenstivity;
		GLfloat ySenstivity;
		bool EnableXMovement;
		bool EnableYMovement;
		GLfloat MaxXMovement, MinXMovement;
		GLfloat MaxYMovement, MinYMovement;
		GLboolean ConstrainX, ConstrainY;

		void Start() override {
			this->m_Camera = Camera::main;
			
			xSenstivity = ySenstivity = SENSTIVITY;
						
			m_xOffset = 0;
			m_yOffset = 0;

			MaxXMovement = 360.0f;
			MinXMovement = -360.0f;
			
			MaxYMovement = 89.0f;
			MinYMovement = -89.0f;

			ConstrainX = false;
			ConstrainY = true;

			EnableXMovement = true;
			EnableYMovement = true;
		}
		void Update() override {
			ProcessMouseEvent(InputManager::GetDeltaX(), InputManager::GetDeltaY());

			if (InputManager::GetKey(KeyCode::E))
				Camera::main->Fly(.05f * Time::deltaTime);
			
			if (InputManager::GetKey(KeyCode::Q))
				Camera::main->Fly(-(.05f * Time::deltaTime));


			if (InputManager::GetKey(KeyCode::UpArrow))
				Camera::main->Walk((.05f * Time::deltaTime));
			if (InputManager::GetKey(KeyCode::DownArrow))
				Camera::main->Walk(-(.05f * Time::deltaTime));
			if (InputManager::GetKey(KeyCode::RightArrow))
				Camera::main->Strafe(-.05f * Time::deltaTime);
			if (InputManager::GetKey(KeyCode::LeftArrow))
				Camera::main->Strafe((.05f * Time::deltaTime));
		}
		inline void OnEnable() override{
			Camera::main->overwriteTarget = false;
		//	fprintf(stdout, "Enabled called");
		}
		void ProcessMouseEvent(GLfloat xOffset, GLfloat yOffset) const
		{
			if (EnableXMovement)
			{
				xOffset *= this->xSenstivity;
				m_Camera->Yaw += xOffset;
				if (ConstrainX)
				{
					if (m_Camera->Yaw > MaxXMovement)
						m_Camera->Yaw = MaxXMovement;
					if (m_Camera->Yaw < MinXMovement)
						m_Camera->Yaw = MinXMovement;
				}
			}
			if (EnableYMovement)
			{
				yOffset *= this->ySenstivity;
				m_Camera->Pitch += yOffset;
				if (ConstrainY)
				{
					if (m_Camera->Pitch > MaxYMovement)
						m_Camera->Pitch = MaxYMovement;
					if (m_Camera->Pitch < MinYMovement)
						m_Camera->Pitch = MinYMovement;
				}
			}

			m_Camera->UpdateCameraVectors();
		}
	};
}
