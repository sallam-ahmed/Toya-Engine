#include "Camera.hpp"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include "../CoreDrivers/Screen.hpp"


namespace Toya
{
	namespace Components
	{
		Camera* Camera::main;

		Camera::Camera(Graphics::Window* activeWindow, glm::vec3& worldUp)
		{
			main = this;
			m_Direction = glm::vec3(0, 0, -1.0f);
			
			farPlane = FAR;
			nearPlane = NEAR;

			Projection = Perspective;
			_window = activeWindow;
			_aspect = activeWindow->GetWidth() / static_cast<GLfloat>(activeWindow->GetHeight());
			m_WorldUp = worldUp;
			Yaw = YAW;
			Pitch = PITCH;
			fieldOfView = FOV;
			UpdateCameraVectors();
		}
		Camera::~Camera()
		{
		}

		glm::mat4* Camera::GetWorldToViewMatrix() 
		{
			return &m_ViewMatrix;
		}
		glm::mat4* Camera::GetProjcetionMatrix() 
		{
			return &m_ProjectionMatrix;
		}

		void Camera::LookAt(Transform* target)
		{
		}

		glm::vec3 Camera::_getLookDirection() const
		{
			return glm::vec3(-m_Direction);
		}
		void Camera::UpdateCameraVectors()
		{
			glm::vec3 front;

			front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
			front.y = sin(glm::radians(this->Pitch));
			front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

			this->m_Direction = glm::normalize(front);
			this->m_Right = glm::normalize(glm::cross(this->m_Direction, this->m_WorldUp));
			this->m_Up= glm::normalize(glm::cross(this->m_Right, this->m_Direction));

		}
		void Camera::UpdateViewMatrix()
		{
			if (!overwriteTarget) {
				glm::vec3 center = transform->Position + this->_getLookDirection();
				m_ViewMatrix = glm::lookAt(transform->Position, center, m_Up);
			}
			else
			{				
				glm::vec3 front;
				front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
				front.y = sin(glm::radians(this->Pitch));
				front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

				this->m_Direction = glm::normalize(front);

				this->m_Right = glm::normalize(glm::cross(this->m_Direction, this->m_WorldUp));
				this->m_Up = glm::normalize(glm::cross(this->m_Right, this->m_Direction));

				m_ViewMatrix = glm::lookAt(transform->Position, LookTarget->Position, m_Up);
			}
		}
		void Camera::SetProjection()
		{
			switch (Projection)
			{
			case Orthographic:
				m_ProjectionMatrix = glm::ortho(0.0f, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, 0.0f, nearPlane, farPlane);
				break;
			case Perspective:
				//fprintf(stdout, "Setting projection, %f, %f, %f, %f, %f\n", fieldOfView, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, nearPlane, farPlane);
				if (CoreDrivers::Screen::ScreenWidth != 0)
				{
					m_ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), CoreDrivers::Screen::ScreenWidth / static_cast<GLfloat>(CoreDrivers::Screen::ScreenHeight), nearPlane, farPlane);
				}
				break;
			default: ;
			}
		}
		void Camera::Slide(float stepR, float stepU, float stepD) const
		{
			transform->Position += m_Right * stepR;
			transform->Position += m_Up * stepU;
			transform->Position += m_Direction * stepD;

			/*	Self->Translate(m_Right, stepR);
				Self->Translate(m_Up, stepU);
				Self->Translate(m_Direction, stepD);*/
		}
		void Camera::Walk(float dist)

		{
			//Self->Position -= glm::vec3(dist * m_Direction);
			transform->Translate(m_Direction, -dist);
		}
		void Camera::Strafe(float dist)

		{
			//Self->Position += m_Right * dist;
			transform->Translate(m_Right, dist);
		}
		void Camera::Fly(float dist)

		{
			//Self->Position += m_Up * dist;
			transform->Translate(m_Up, dist);
			//	Self->Translate(m_Up, dist);
		}
	}
}
