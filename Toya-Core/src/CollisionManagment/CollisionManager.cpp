#include "CollisionManager.hpp"
#include "../Components/BoxCollider.hpp"


namespace Toya
{
	namespace CoreDrivers
	{
		std::vector<Toya::Components::Transform*> CollisionManager::Collidables;
		CollisionManager::CollisionManager()
		{
		}
		CollisionManager::~CollisionManager()
		{
		}
		void CollisionManager::AddListener(Components::Transform* listener)
		{
			Collidables.push_back(listener);
		}
		void CollisionManager::CollisionUpdateLoop()
		{
			for (auto i = 0; i < Collidables.size(); i++)
			{
				for (auto j = i + 1; j < Collidables.size(); j++)
				{
					auto boxCollider = static_cast<Components::BoxCollider*>(Collidables[i]->GetComponent<Components::BoxCollider>());
					auto otherBoxCollider = static_cast<Components::BoxCollider*>(Collidables[j]->GetComponent<Components::BoxCollider>());

					if (boxCollider->GetBoundingBox()->IsIntersecting(otherBoxCollider->GetBoundingBox()))
					{

						for (auto c = 0; c < Collidables[i]->Behaviours.size(); c++)
						{
							auto behaviour = Collidables[i]->Behaviours[c];
							behaviour->_onCollision(Collidables[j], true);
							static_cast<Components::BoxCollider*>(behaviour->transform->GetComponent<Components::BoxCollider>())->Free = false;
						}
						/*for (Components::Behaviour* behaviour : Collidables[i]->Behaviours)
						{
							behaviour->_onCollision(Collidables[j],true);
							behaviour->transform->GetComponent<Components::BoxCollider>()->Free = false;
							fprintf(stdout, "t: %p.\n", behaviour->transform);
							fprintf(stdout, "COLS %p.\n", boxCollider);
						}*/
						for (auto c = 0; c < Collidables[j]->Behaviours.size(); c++)
						{
							auto behaviour = Collidables[j]->Behaviours[c];
							behaviour->_onCollision(Collidables[i], true);
							static_cast<Components::BoxCollider*>(behaviour->transform->GetComponent<Components::BoxCollider>())->Free = false;
						}
						/*for (Components::Behaviour* behaviour : Collidables[j]->Behaviours)
						{
							behaviour->_onCollision(Collidables[i],true);
							behaviour->transform->GetComponent<Components::BoxCollider>()->Free = false;
						}*/
					}
					else
					{
						for (auto c = 0; c < Collidables[i]->Behaviours.size(); c++)
						{
							auto behaviour = Collidables[i]->Behaviours[c];
							if (behaviour->_collided && behaviour->_lastCollision == Collidables[j])
							{
								behaviour->_onCollision(Collidables[j], false);
								static_cast<Components::BoxCollider*>(behaviour->transform->GetComponent<Components::BoxCollider>())->Free = true;
							}
						}
						/*for (Components::Behaviour* behaviour : Collidables[i]->Behaviours)
						{
							if (behaviour->_collided && behaviour->_lastCollision == Collidables[j])
							{
								behaviour->_onCollision(Collidables[j], false);
								behaviour->transform->GetComponent<Components::BoxCollider>()->Free = true;
							}
						}*/
						for (int c = 0; c < Collidables[j]->Behaviours.size(); ++c)
						{
							auto behaviour = Collidables[j]->Behaviours[c];
							if (behaviour->_collided&& behaviour->_lastCollision == Collidables[i])
							{
								behaviour->_onCollision(Collidables[i], false);
								static_cast<Components::BoxCollider*>(behaviour->transform->GetComponent<Components::BoxCollider>())->Free = true;
							}
						}
						/*for (Components::Behaviour* behaviour : Collidables[j]->Behaviours)
						{
							if (behaviour->_collided&& behaviour->_lastCollision == Collidables[i])
							{
								behaviour->_onCollision(Collidables[i], false);
								behaviour->transform->GetComponent<Components::BoxCollider>()->Free = true;
							}
						}*/
					}
				}
			}
		}
		void CollisionManager::UnregisterObject(Components::Transform* obj)
		{
			auto i = 0, c = 0;
			for (i = 0; i < Collidables.size(); i++)
			{

				if (Collidables[i] != obj) 
				{

					for (auto b : Collidables[i]->Behaviours)
					{
						if (b->_lastCollision == obj) {
							b->transform->GetComponent<Components::BoxCollider>()->Free = true;
							b->_onCollision(obj, false);
						}
					}
				}
				else
				{
					c = i;
				}
			}
			Collidables.erase(Collidables.begin() + c);

		}
	}
}
