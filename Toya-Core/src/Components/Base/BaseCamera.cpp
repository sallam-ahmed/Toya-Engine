#if 0
#include "BaseCamera.hpp"


namespace Toya
{
	namespace Components
	{
		namespace Base
		{
			BaseCamera::~BaseCamera()
			{
			}

			Matrix4x4 BaseCamera::GetProjcetionMatrix() const
			{
				return m_ProjectionMatrix;
			}
			glm::vec3 BaseCamera::_getLookDirection() const
			{
				return glm::vec3(-m_Direction);
			}
			void BaseCamera::UpdateViewMatrix()
			{
				glm::vec3 center = Self->position + _getLookDirection();
				m_ViewMatrix = Math::Matrix4x4(glm::lookAt(GetTransform()->position, center, m_Up));
			}

			void BaseCamera::SetProjection()
			{
				switch (CameraProjection)
				{
				case Orthographic:
					if (CoreDrivers::Screen::ScreenWidth != 0)
					{
						m_ProjectionMatrix = Matrix4x4(glm::ortho(0.0f, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, 0.0f, nearPlane, farPlane));
					}
					break;
				case Perspective:
					if (CoreDrivers::Screen::ScreenWidth != 0)
					{
						m_ProjectionMatrix = Matrix4x4(glm::perspective(fieldOfView, CoreDrivers::Screen::ScreenWidth / static_cast<GLfloat>(CoreDrivers::Screen::ScreenHeight), nearPlane, farPlane));
					}
					break;
				default:;
				}
			}
		}
	}
}
#endif