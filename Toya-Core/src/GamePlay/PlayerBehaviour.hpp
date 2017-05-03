#pragma once
#include "../Input/InputManager.hpp"
#include "../Components/Base/Transform.hpp"
#include "../CoreDrivers/Time.hpp"

#define HORIZONTAL_AXIS glm::vec3(0,0,1)
#define VERTICAL_AXIS glm::vec3(1,0,0)
namespace GamePlay
{
	using namespace Toya::Input;
	class PlayerBehaviour : public Toya::Components::Behaviour
	{
	public:
		float MovementSpeed = 0.05f;
		
		inline void Start() override{
			fprintf(stdout, "Player Behaviour Started.\n");
		}

		inline void Update() override{
			//Handle Movement
			if(InputManager::GetKey(KeyCode::W))
			{
				transform->Translate(HORIZONTAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(HORIZONTAL_AXIS, 10.0f);
			}
			if(InputManager::GetKey(KeyCode::S))
			{
				transform->Translate(-HORIZONTAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(HORIZONTAL_AXIS, -10.0f);
			}
			if (InputManager::GetKey(KeyCode::D))
			{
				transform->Translate(-VERTICAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(VERTICAL_AXIS, 10.0f);
			}
			if(InputManager::GetKey(KeyCode::A))
			{
				transform->Translate(VERTICAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(VERTICAL_AXIS, 10.0f);
			}
		}
	};
}
