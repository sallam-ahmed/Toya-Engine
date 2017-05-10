#pragma once
#include "../CoreDrivers/RenderDriver.hpp"
#include "../CollisionManagment/CollisionManager.hpp"
#include "../Components/BoxCollider.hpp"

namespace Toya
{
	namespace SceneManagement
	{

		using namespace Toya::CoreDrivers;
		class Scene
		{
		private:
			std::vector<Components::Model*> m_ScenePhysicsListeners;
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

			inline void UnregisterObject(Components::Transform* obj)
			{
				for (int i = 0; i < m_SceneRenderModels.size(); i++)
				{
					if (obj == m_SceneRenderModels[i]->transform)
					{
						m_SceneRenderModels.erase(m_SceneRenderModels.begin() + i);
						return;
					}
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
					{
						//fprintf(stdout, "Added Model to vector \n");
						m_SceneRenderModels.push_back(mdl);
					}

					auto col = SceneObjects[i]->transform->GetComponent<Components::BoxCollider>();
					if (col != nullptr)
						CollisionManager::AddListener(col->transform);
				}
				
			}

			inline std::vector<Components::Model*> GetSceneRenderModels()
			{
				return m_SceneRenderModels;
			}
			void SceneUpdate() const
			{
				//Input reading
				for (auto col : SceneObjects)
				{
					for (auto b : col->transform->Behaviours)
					{
						if(b->enabled)
							b->Update();
					}
				}
				//Render Drawing
				RenderManager::RenderUpdateLoop(m_SceneRenderModels);
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
			Components::GameObject* AddObject(Components::GameObject* obj)
			{
				m_RunTimeObjects.push_back(obj);
			}
		};
		Scene* Scene::activeScene;

	}
		

}
