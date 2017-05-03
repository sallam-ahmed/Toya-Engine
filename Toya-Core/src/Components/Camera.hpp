#pragma once
#include "../Graphics/Window.hpp"
#include "../Math/Math.hpp"
#include <GLM/glm.hpp>
#include "Base/Transform.hpp"



using namespace Toya::Math;
namespace Toya
{
	namespace Components
	{
		enum ProjectionMode
		{
			Orthographic = 0,
			Perspective = 1
		};
		class FPSCameraController;
		
		class FPSCamera;
		class Camera : public Component
		{
	
			friend class FPSCameraController;
			const GLfloat YAW = 0.0f;
			const GLfloat PITCH = 0.0f;
			const GLfloat SPEED = 3.0f;
			const GLfloat SENSITIVTY = 0.25f;
			const GLfloat FOV = 60.0f;
			const GLfloat FAR = 100.0f;
			const GLfloat NEAR = 0.1f;

			Matrix4x4 m_ViewMatrix;
			Matrix4x4 m_ProjectionMatrix;
			glm::vec3 m_Up;
			glm::vec3 m_Right;
			glm::vec3 m_Direction;
			GLfloat _aspect;
			Graphics::Window *_window;
			glm::vec3 m_WorldUp;

		public:
			Camera(Graphics::Window*,glm::vec3&);
			//Camera(Graphics::Window* activeWindow, glm::vec3*  pos, float fov, float near, float far, ProjectionMode projection_mode, const glm::vec3& initialUp, const glm::vec3& initialCenter);
			~Camera();
			inline glm::vec3 GetLookDirection() const
			{
				return m_Direction;
			}
			//Transform* GetTransform() const { return transform; }
			glm::vec3 LookTarget;
			bool overwriteTarget;

			float fieldOfView;
			float nearPlane;
			float farPlane;
			static Camera* main;
			ProjectionMode Projection;
			
			GLfloat	  Yaw;
			GLfloat	  Pitch;

			Math::Matrix4x4 GetWorldToViewMatrix() const;
			Math::Matrix4x4 GetProjcetionMatrix() const;

			void LookAt(Transform* target);
			void UpdateViewMatrix();
			void SetProjection();

			float GetYaw() const { return Yaw; }
			float GetPitch() const { return Pitch; }
#if 0
			void Reset(const glm::vec3& position, const glm::vec3 &center, const glm::vec3 &up);
		
			void Roll(float angle);
			void Pitch(float angle);
			void Yaw(float angle);
#endif


			void Walk(float dist) ;
			void Strafe(float dist) ;
			void Fly(float dist) ;
			void Slide(float stepR, float stepU, float stepD) const;
		
			void UpdateCameraVectors();
		private:
			glm::vec3 _getLookDirection() const;
		};

	}
}

