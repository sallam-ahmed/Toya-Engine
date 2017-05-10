#pragma once
#include "../PlayerBehaviour.hpp"
#include "OrbitCamera.hpp"

namespace GamePlay
{
	
	class CameraController : public Toya::Components::Behaviour
	{
		FPSCamera *fpCamera;
		TPSCamera *tpCamera;
		OrbitCamera *obCamera;

	public:
		void Start() override
		{
			transform->Attach(new GamePlay::FPSCamera());
			transform->Attach(new  GamePlay::TPSCamera());
			transform->Attach(new GamePlay::OrbitCamera());

			fpCamera = static_cast<FPSCamera*>(transform->GetBehaviour<FPSCamera>());
			tpCamera = static_cast<TPSCamera*>(transform->GetBehaviour<TPSCamera>());
			obCamera = static_cast<OrbitCamera*>(transform->GetBehaviour<OrbitCamera>());

			fpCamera->ToggleEnable(true);
			tpCamera->ToggleEnable(false);
			obCamera->ToggleEnable(false);

			tpCamera->AutoFindPlayer = true;
			tpCamera->PlayerName = "Player";

			obCamera->AutoFindPlayer = true;
			obCamera->PlayerName = "Player";

			Camera::main->farPlane = 1000.0f;
			Camera::main->Projection = Perspective;
			Camera::main->Yaw = 90.0f;
			Camera::main->Pitch = 0.0f;
			Camera::main->fieldOfView = 60.0f;
			Camera::main->SetProjection();
			Camera::main->UpdateViewMatrix();

			transform->GetComponent<AudioSource>()->Loop = true;
		}
		void OnEnable() override{
		}
		void Update() override
		{

			if(InputManager::GetKey(KeyCode::Alpha1))
			{
				fpCamera->ToggleEnable(true);
				tpCamera->ToggleEnable(false);
				obCamera->ToggleEnable(false);
			}
			if (InputManager::GetKey(KeyCode::Alpha2))
			{
				fpCamera->ToggleEnable(false);
				tpCamera->ToggleEnable(true);
				obCamera->ToggleEnable(false);
			}
			if (InputManager::GetKey(KeyCode::Alpha3))
			{
				fpCamera->ToggleEnable(false);
				tpCamera->ToggleEnable(false);
				obCamera->ToggleEnable(true);
			}
		}
	};
}
