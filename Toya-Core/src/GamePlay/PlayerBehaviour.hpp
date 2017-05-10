#pragma once
#include "../Input/InputManager.hpp"
#include "../Components/Base/Transform.hpp"
#include "../CoreDrivers/Time.hpp"
#include "../GamePlay/Light.hpp"
#include "../CoreDrivers/Time.hpp"
#include "../CoreDrivers/AudioSource.hpp"



#define HORIZONTAL_AXIS glm::vec3(0,0,1)
#define VERTICAL_AXIS glm::vec3(1,0,0)
#define MOVE_EFFECT "res/Audio/roll.mp3"
#define BRICK_SOUND "res/Audio/hit.wav"
#define POINT_SOUND "res/Audio/point.mp3"
namespace GamePlay
{
	using namespace Toya::Input;
	using namespace Toya::CoreDrivers;
	class PlayerBehaviour : public Toya::Components::Behaviour
	{
		AudioSource* audioSource;
	public:
		float MovementSpeed = 0.02f;
		
		inline void Start() override{
			fprintf(stdout, "Player Behaviour Started.\n");
			audioSource = transform->GetComponent<AudioSource>();
		}

		inline void Update() override{
			//Handle Movement
			if(InputManager::GetKey(KeyCode::W))
			{
				transform->Translate(HORIZONTAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(-HORIZONTAL_AXIS, 10.0f);
				audioSource->PlayOnce(MOVE_EFFECT);
			}
			if (InputManager::GetKeyUp(KeyCode::W))
				audioSource->Stop();
				
			if(InputManager::GetKey(KeyCode::S))
			{
				transform->Translate(-HORIZONTAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(HORIZONTAL_AXIS, 10.0f);
				audioSource->PlayOnce(MOVE_EFFECT);
			}
			if (InputManager::GetKeyUp(KeyCode::S))
				audioSource->Stop();
			
			if (InputManager::GetKey(KeyCode::D))
			{
				transform->Translate(-VERTICAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(VERTICAL_AXIS, 10.0f);
				transform->GetComponent<AudioSource>()->PlayOnce(MOVE_EFFECT);
			}
			if (InputManager::GetKeyUp(KeyCode::D))
				audioSource->Stop();
			if(InputManager::GetKey(KeyCode::A))
			{
				transform->Translate(VERTICAL_AXIS, MovementSpeed * Toya::CoreDrivers::Time::deltaTime);
				transform->Rotate(-VERTICAL_AXIS, 10.0f);
				transform->GetComponent<AudioSource>()->PlayOnce(MOVE_EFFECT);
			}
			if (InputManager::GetKeyUp(KeyCode::A))
				audioSource->Stop();
			
		}

		inline void OnEnable() override{
		}
		inline void OnCollision(Toya::Components::Transform* other) override{
			if (other->gameObject->tag == "Brick")
				audioSource->PlayOnce(BRICK_SOUND);
			else if (other->gameObject->tag == "PacPoint")
				audioSource->Play(POINT_SOUND);

		}
		inline void OnCollisionExit(Toya::Components::Transform* other) override{
			fprintf(stdout, "Collision Exit with %p.\n", other);

		}
	};
}
