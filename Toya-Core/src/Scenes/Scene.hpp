#pragma once
#include "../Components/Base/Transform.hpp"
#include "../Graphics/Lighting/Lighting.hpp"
#include "../CoreDrivers/RenderDriver.hpp"

namespace Toya
{
	namespace SceneManagement
	{
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
		public:
			void SceneStart()
			{ 
				for(auto col : SceneObjects)
				{
					if(static_cast<CollidableMesh*>(col) == 0)
						m_ScenePhysicsListeners.push_back(static_cast<CollidableMesh*>(col));
				}
			}
			void SceneUpdate() const
			{
				//Input reading
				//Render Drawing
				SceneRenderer->RenderUpdateLoop(SceneObjects);
				//Collision Detection
				CollisionManager::CheckCollision(m_ScenePhysicsListeners);
			
			}
			void SceneEnd() const
			{
				//Destroy All Objects
				for (auto i : SceneObjects)
					delete i;
			}
			Scene() = default;
			~Scene()
			{
				SceneEnd();
			}
			std::vector<Components::Transform*> SceneObjects;
			Graphics::Lighting::LightManager* SceneLightManager;
			CoreDrivers::RenderManager* SceneRenderer;
		};
	}
}
