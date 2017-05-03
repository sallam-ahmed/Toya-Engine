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
						Camera::main->overwriteTarget = true;
					}
				}
				else {
					this->enabled = false;
					fprintf(stdout, "ERROR: Target for TPSCamera Behaviour is null Behaviour is stopped.\n");
				}
			}
			else
			{
				Toya::Components::Camera::main->overwriteTarget = true;
			}
		}
		void Update() override{
			Camera::main->LookTarget = -(target->Position);
			auto pitch = glm::radians(Camera::main->GetPitch());
			auto yaw = glm::radians(Camera::main->GetYaw());
			auto cosPitch = glm::cos(pitch);
			auto sinPitch = glm::sin(pitch);
			auto cosYaw = glm::cos(yaw);
			auto sinYaw = glm::sin(yaw);
			
			auto offset = glm::vec3((Distance)* cosPitch * sinYaw, (Height)* sinPitch, (Distance)*cosYaw* sinPitch);
			Camera::main->transform->Position = 2.0f * (target->Position  + Camera::main->GetLookDirection());
			if (InputManager::GetKey(KeyCode::G))
			{
				Height += 10;
				fprintf(stdout, "Height Increased %f.\n",Height);
			}
			
			//glm::vec3((target->Position.x + Distance) * glm::cos(Camera::main->GetPitch()) * glm::sin(Camera::main->GetYaw()), (target->Position.y +Height)   * glm::sin(Camera::main->GetPitch()), (target->Position.z + Distance)  * glm::cos(Camera::main->GetYaw()) * glm::sin(Camera::main->GetPitch()));
				
			/*if (InputManager::GetKey(KeyCode::Alpha5))
			{
				auto pos = Camera::main->transform->Position;
				auto pos2 = target->Position;
				fprintf(stdout, "CAMERA : %f,%f,%f -- TARGET : %f,%f,%f\n", pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z);
			}*/
		}
	};
}