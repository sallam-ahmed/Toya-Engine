#pragma once
#include "../PlayerBehaviour.hpp"
#include "../../Components/Camera.hpp"
#include "../../Utils/ObjectUtils.hpp"

namespace GamePlay
{
	using namespace Toya::Components;
	class OrbitCamera : public Behaviour
	{
	public:
		Transform* target;
		float Distance;
		float Height;
		bool AutoFindPlayer;
		char* PlayerName;


		float xSenstivity, ySenstivity;

		void Start() override {

			xSenstivity = ySenstivity = 0.7f;
			Distance = Height = 20.0f;

			if (target == nullptr)
			{
				if (AutoFindPlayer) 
				{
					auto obj = Toya::FindGameObject(PlayerName);
					if (obj != nullptr)
					{

						target = obj->transform;
						if (enabled) {
							Camera::main->overwriteTarget = true;

							Camera::main->transform->Position = target->Position - (glm::vec3(0, 0, 1) * Distance);
							Camera::main->transform->Position.y += Height;
							Camera::main->LookTarget = (target);
						}
					}
				}
				else {
					this->enabled = false;
					fprintf(stdout, "ERROR: Target for TPSCamera Behaviour is null Behaviour is stopped.\n");
				}
			}
			else
			{
				if(enabled)
				{
					Camera::main->overwriteTarget = true;
					Camera::main->transform->Position = target->Position - (glm::vec3(0, 0, 1) * Distance);
					Camera::main->transform->Position.y += Height;
					Camera::main->LookTarget = (target);
				}
			}

		}
		void OnEnable() override{
			
			Camera::main->overwriteTarget = true;
			Camera::main->transform->Position = target->Position - (glm::vec3(0, 0, 1) * Distance);
			Camera::main->transform->Position.y += Height;
			Camera::main->LookTarget = (target);

		}
		void Update() override{
			
			ProcessMouseEvent(InputManager::GetDeltaX());

			if (InputManager::GetKey(KeyCode::PadAdd))
				Height += 2;
			else if (InputManager::GetKey(KeyCode::PadSubtract))
				Height -= 2;
		}
		void ProcessMouseEvent(GLfloat xOffset) const
		{
			xOffset *= this->xSenstivity;
			Camera::main->Yaw += xOffset;

			
			Camera::main->UpdateCameraVectors();
			
			Camera::main->transform->Position = target->Position - (Camera::main->GetLookDirection() * Distance);
			Camera::main->transform->Position.y += Height;

		}
	};
}
