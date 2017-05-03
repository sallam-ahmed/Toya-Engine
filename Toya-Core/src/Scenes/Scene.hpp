#pragma once
#include "../Graphics/Lighting/Lighting.hpp"
#include "../CoreDrivers/RenderDriver.hpp"

namespace Toya
{
	namespace SceneManagement
	{

		using namespace Toya::CoreDrivers;
		class CollidableMesh : public Components::Transform
		{
			
		};
		class CollisionManager
		{
		public:
			static void CheckCollision(std::vector<CollidableMesh*> vec);
		};
		class Scene
		{
		private:
			std::vector<CollidableMesh*> m_ScenePhysicsListeners;
			std::vector<Components::Model*> m_SceneRenderModels;
			std::vector<Components::GameObject*>m_RunTimeObjects;
		public:
			static Scene* activeScene;
			Scene()
			{
				if (activeScene == nullptr)
					activeScene = this;
				else
				{
					activeScene->SceneEnd();
					activeScene = this;
				}
			}
			glm::vec3 WorldUp = glm::vec3(0, 1, 0);
			void SceneStart()
			{ 
				//Light Initialize here
				Input::InputManager::SetCursorLockState(Input::LockState::Locked);
				RenderManager::RenderInitialize();;
				for (int i = 0; i < SceneObjects.size(); ++i)
				{
					for (int j = 0; j < SceneObjects[i]->transform->Behaviours.size(); ++j)
					{
						
						SceneObjects[i]->transform->Behaviours[j]->Start();
					}
					
					auto mdl = SceneObjects[i]->transform->GetComponent<Components::Model>();
					
					if (mdl != nullptr)
						m_SceneRenderModels.push_back(mdl);
				}
				//for(auto col : SceneObjects)
				//{
				//	/******************************************************/
				//	for(auto b : col->transform->Behaviours)
				//	{
				//		b->Start();
				//	}
				//	/*****************************************************/
				//	auto mdl = col->transform->GetComponent<Components::Model>();
				//	if(mdl != nullptr)
				//	{
				//		m_SceneRenderModels.push_back(mdl);
				//	}
				//	/*****************************************************/
				//}

				//for (auto rObj : m_RunTimeObjects)
				//{
				//	for (auto b : rObj->transform->Behaviours)
				//	{
				//		b->Start();
				//	}
				//	/*****************************************************/
				//	auto mdl = rObj->transform->GetComponent<Components::Model>();
				//	if (mdl != nullptr)
				//	{
				//		m_SceneRenderModels.push_back(mdl);
				//	}
				//}
			}
			void SceneUpdate() const
			{
				//Input reading
				//Render Drawing
				RenderManager::RenderUpdateLoop(m_SceneRenderModels);
				for (auto col : SceneObjects)
				{
					for (auto b : col->transform->Behaviours)
					{
						//fprintf(stdout, "Updating Behavior of %s\n", b->transform->gameObject->name);
						if(b->enabled)
							b->Update();
					}
				}
				//Collision Detection			
			}
			void SceneEnd() const
			{
				//Destroy All Objects
				//for (auto i : SceneObjects)
				//	delete i;
			}
			~Scene()
			{
				SceneEnd();
			}
			std::vector<Components::GameObject*> SceneObjects;
			Graphics::Lighting::LightManager* SceneLightManager;

			Components::GameObject* AddObject(Components::GameObject* obj)
			{
				m_RunTimeObjects.push_back(obj);
			}

		};
		Scene* Scene::activeScene;

	}
		

}
