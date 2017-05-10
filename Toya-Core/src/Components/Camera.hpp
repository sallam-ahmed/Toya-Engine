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
		class OrbitCamera;
		class Camera : public Component
		{
	
			friend class FPSCameraController;
			friend class OrbitCamera;
			const GLfloat YAW = 45.0f;
			const GLfloat PITCH = 0.0f;
			const GLfloat SPEED = 3.0f;
			const GLfloat SENSITIVTY = 0.25f;
			const GLfloat FOV = 60.0f;
			const GLfloat FAR = 100.0f;
			const GLfloat NEAR = 0.1f;

			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ProjectionMatrix;
			glm::vec3 m_Up;
			glm::vec3 m_Right;
			glm::vec3 m_Direction;
			GLfloat _aspect;
			Graphics::Window *_window;
			glm::vec3 m_WorldUp;

		public:
			Camera(Graphics::Window*,glm::vec3&);
			~Camera();
			inline glm::vec3 GetLookDirection() const
			{
				return m_Direction;
			}

			Transform* LookTarget;
			bool overwriteTarget;

			float fieldOfView;
			float nearPlane;
			float farPlane;
			static Camera* main;
			ProjectionMode Projection;
			
			GLfloat	  Yaw;
			GLfloat	  Pitch;

			glm::mat4* GetWorldToViewMatrix() ;
			glm::mat4* GetProjcetionMatrix() ;

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

