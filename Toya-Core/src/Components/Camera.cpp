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
			//transform->Position = *pos;
			m_Yaw = YAW;
			m_Pitch = PITCH;
			fieldOfView = FOV;
			_updateCameraVectors();
		}
#if 0
		Camera::Camera(Graphics::Window* activeWindow, glm::vec3* pos, float fov, float near, float far, ProjectionMode projection_mode, const glm::vec3& initialUp, const glm::vec3& initialCenter)
		{
			fieldOfView = fov;
			nearPlane = near;
			farPlane = far;
			Projection = projection_mode;
			_window = activeWindow;
			_aspect = activeWindow->GetWidth() / static_cast<GLfloat>(activeWindow->GetHeight());
			m_Up = initialUp;
			this->Reset(*pos, initialCenter, m_Up);
		}
#endif
		Camera::~Camera()
		{
		}

		Math::Matrix4x4 Camera::GetWorldToViewMatrix() const
		{
			return m_ViewMatrix;
		}
		Math::Matrix4x4 Camera::GetProjcetionMatrix() const
		{
			return m_ProjectionMatrix;
		}
		glm::vec3 Camera::_getLookDirection() const
		{
			return glm::vec3(-m_Direction);
		}
		void Camera::_updateCameraVectors()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
			front.y = sin(glm::radians(this->m_Pitch));
			front.z = sin(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
			this->m_Direction = glm::normalize(front);
			this->m_Right = glm::normalize(glm::cross(this->m_Direction, this->m_WorldUp));
			this->m_Up= glm::normalize(glm::cross(this->m_Right, this->m_Direction));
		}
#if 0
		void Camera::Reset(const glm::vec3& m_Position, const glm::vec3& center, const glm::vec3& up)
		{
			//fprintf(stdout, "UP1 -> %f,%f,%f", m_Up.x, m_Up.y, m_Up.z);
			this->Self->Position = m_Position;
			m_Direction = m_Position - center;
			m_Right = glm::cross(m_Up, m_Direction);
			m_Up = glm::cross(m_Direction, m_Right);
			//fprintf(stdout, "UP2 -> %f,%f,%f", m_Up.x, m_Up.y, m_Up.z);
			//Normalizing

			auto upNorm = glm::normalize(m_Up);
			m_Up = glm::vec3(upNorm);
			//fprintf(stdout, "UP3 -> %f,%f,%f", m_Up.x, m_Up.y, m_Up.z);
			auto rightNorm = glm::normalize(m_Right);
			m_Right = glm::vec3(rightNorm);
			auto dirNorm = glm::normalize(m_Direction);
			m_Direction = glm::vec3(dirNorm);
			UpdateViewMatrix();
		}
#endif
		void Camera::UpdateViewMatrix()
		{
			glm::vec3 center = transform->Position + this->_getLookDirection();
			m_ViewMatrix = Math::Matrix4x4(glm::lookAt(transform->Position, center, m_Up));
		}
		void Camera::SetProjection()
		{
			switch (Projection)
			{
			case Orthographic:
				m_ProjectionMatrix = Matrix4x4(glm::ortho(0.0f, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, 0.0f, nearPlane, farPlane));
				break;
			case Perspective:
				//fprintf(stdout, "Setting projection, %f, %f, %f, %f, %f\n", fieldOfView, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, nearPlane, farPlane);
				if (CoreDrivers::Screen::ScreenWidth != 0)
				{
					m_ProjectionMatrix = Matrix4x4(glm::perspective(glm::radians(fieldOfView), CoreDrivers::Screen::ScreenWidth / static_cast<GLfloat>(CoreDrivers::Screen::ScreenHeight), nearPlane, farPlane));
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
#if 0
		void Camera::Yaw(float angleDegrees)
		{

			m_Yaw += angleDegrees;
			m_Direction = glm::vec3(glm::rotate(m_Direction, glm::radians(angleDegrees), m_Up));
			m_Right = glm::vec3(glm::rotate(m_Right, glm::radians(angleDegrees), m_Up));
		}


		void Camera::Pitch(float angleDegrees)
		{
			m_Up = glm::vec3(glm::rotate(m_Up, glm::radians(angleDegrees), m_Right));
			m_Direction = glm::vec3(glm::rotate(m_Direction, glm::radians(angleDegrees), m_Right));
		}

		void Camera::Roll(float angleDegrees)

		{
			m_Right = glm::vec3(glm::rotate(m_Right, glm::radians(angleDegrees), m_Direction));
			m_Up = glm::vec3(glm::rotate(m_Up, glm::radians(angleDegrees), m_Direction));
		}
#endif
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
