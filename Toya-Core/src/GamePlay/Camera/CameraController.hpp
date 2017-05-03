#pragma once
#include "../PlayerBehaviour.hpp"

namespace GamePlay
{
	
	class CameraController : public Toya::Components::Behaviour
	{
		FPSCamera *fpCamera;
		TPSCamera *tpCamera;

	public:
		void Start() override
		{
			transform->Attach(new GamePlay::FPSCamera());
			transform->Attach(new  GamePlay::TPSCamera());

			fpCamera = static_cast<FPSCamera*>(transform->GetBehaviour<FPSCamera>());
			tpCamera = static_cast<TPSCamera*>(transform->GetBehaviour<TPSCamera>());

			fpCamera->enabled = false;
			tpCamera->enabled = true;

			tpCamera->AutoFindPlayer = true;
			tpCamera->PlayerName = "Player";

			Camera::main->farPlane = 1000.0f;
			Camera::main->Projection = Perspective;
			Camera::main->SetProjection();
			Camera::main->UpdateViewMatrix();
		}
		void Update() override
		{

			if(InputManager::GetKey(KeyCode::F))
			{
				fpCamera->enabled = !fpCamera->enabled;
				tpCamera-> enabled = !tpCamera->enabled;
			}
		}
	};
}
