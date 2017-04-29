#pragma once
#if 0

#include "../../Graphics/Window.hpp"
#include "../../Math/Math.hpp"
#include "../Camera.hpp"
#include "../../CoreDrivers/Screen.hpp"
#include "../Transform.hpp"


namespace Toya
{
	namespace Components
	{
		namespace Base
		{
			class BaseCamera : public Transform
			{
			protected:
				Matrix4x4 m_ViewMatrix;
				Matrix4x4 m_ProjectionMatrix;
				glm::vec3 m_Up;
				glm::vec3 m_Right;
				glm::vec3 m_Direction;
				GLfloat _aspect;
				Graphics::Window *_window;
			public:
				BaseCamera() = default;
				virtual ~BaseCamera();
				inline virtual Transform* GetTransform() const override { return Self; }
				float fieldOfView;
				float nearPlane;
				float farPlane;
				ProjectionMode CameraProjection;
				virtual Math::Matrix4x4 GetWorldToViewMatrix() const = 0;
				virtual Matrix4x4 GetProjcetionMatrix() const;
				virtual void UpdateViewMatrix();
				virtual void SetProjection();
			protected:
				virtual glm::vec3 BaseCamera::_getLookDirection() const;
			};


		}
	}
}
#endif