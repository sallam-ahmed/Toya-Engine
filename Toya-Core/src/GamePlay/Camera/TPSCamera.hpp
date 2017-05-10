#pragma once
#include "../../Input/InputManager.hpp"
#include "../../Components/Base/Transform.hpp"
#include "../../CoreDrivers/Time.hpp"
#include "../../Components/Camera.hpp"

#define HORIZONTAL_AXIS glm::vec3(0,0,1)
#define VERTICAL_AXIS glm::vec3(1,0,0)
namespace GamePlay
{
	using namespace Toya::Input;
	using namespace Toya::Components;
	class TPSCamera : public Toya::Components::Behaviour
	{
	public:
		Toya::Components::Transform* target;
		float Height = 20.0f;
		float Distance = 20.0f;
		bool AutoFindPlayer;
		char* PlayerName;
		
		void Start() override{
			
			if(target == nullptr)
			{
				if (AutoFindPlayer) {
				
					auto obj = Toya::FindGameObject(PlayerName);
					if (obj != nullptr)
					{
						target = obj->transform;
						if (enabled) 
						{
						
							Camera::main->overwriteTarget = true;
							Camera::main->transform->Position = target->Position - (Camera::main->GetLookDirection() * Distance);
							Camera::main->transform->Position.y += Height;
							Camera::main->LookTarget = (target);// ->Position);
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
				if (enabled) {
					Toya::Components::Camera::main->overwriteTarget = true;
					Camera::main->transform->Position = target->Position - (Camera::main->GetLookDirection() * Distance);
					Camera::main->transform->Position.y += Height;
					Camera::main->LookTarget = (target);
				}
			}

		}

		void OnEnable() override{

			Camera::main->overwriteTarget = true;
			Camera::main->LookTarget = (target);
			
			Camera::main->Yaw = 90.0f;
			Camera::main->Pitch = 0.0f;

			Camera::main->UpdateViewMatrix();

			Camera::main->transform->Position = target->Position - (Camera::main->GetLookDirection() * Distance);
			Camera::main->transform->Position.y += Height;
		}
		void Update() override{

			//T = P + D
			Camera::main->transform->Position = target->Position - (Camera::main->GetLookDirection() * Distance);
			Camera::main->transform->Position.y += Height;

			if (InputManager::GetKey(KeyCode::PadAdd))
				Height += 2;
			else if (InputManager::GetKey(KeyCode::PadSubtract))
				Height -= 2;
			if (InputManager::GetKey(KeyCode::PadDivide))
				Distance -= 2;
			else if (InputManager::GetKey(KeyCode::PadMultiply))
				Distance += 2;
		}
	};
}