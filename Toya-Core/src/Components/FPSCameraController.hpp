#pragma once
#include "../Math/Math.hpp"
#include "Camera.hpp"

namespace Toya
{
	namespace Components
	{
		class FPSCameraController : public Component
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
			FPSCameraController(Camera* activeCamera)
			{
				xSenstivity = ySenstivity = SENSTIVITY;
				this->m_Camera = activeCamera;
				EnableXMovement = true;
				EnableYMovement = false;
				m_xOffset = 0;
				m_yOffset = 0;
				MaxXMovement = 360.0f;
				MinXMovement = -360.0f;
				MaxYMovement = 89.0f;
				MinYMovement = -89.0f;
				ConstrainX = false;
				ConstrainY = false;
			}
			void ProcessMouseEvent(GLfloat xOffset, GLfloat yOffset) const
			{
				if (EnableXMovement)
				{
					xOffset *= this->xSenstivity;
					m_Camera->Yaw += xOffset;
					if (ConstrainX)
					{
						if (m_Camera->Pitch > MaxXMovement)
							m_Camera->Pitch = MaxXMovement;
						if (m_Camera->Pitch < MinXMovement)
							m_Camera->Pitch = MinXMovement;
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
}
