#pragma once
#include "PlayerBehaviour.hpp"

namespace GamePlay
{
	class PacPoint: public Toya::Components::Behaviour
	{
	public:
		void Start() override
		{

		}

		void Update() override
		{

		}

		void OnEnable() override
		{
		}

		void OnCollision(Toya::Components::Transform* other) override
		{
			if (other->gameObject->name == "Player")
			{
				fprintf(stdout, "Scored !.\n");
				//Toya::CoreDrivers::CollisionManager::UnregisterObject(this->transform);
				Toya::Destroy(gameObject);
			}
		}

		void OnCollisionExit(Toya::Components::Transform* other) override
		{
		}

		~PacPoint() override{
		
		}
	};
}
