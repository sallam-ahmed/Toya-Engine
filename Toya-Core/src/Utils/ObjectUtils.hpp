#pragma once
#include "../Scenes/Scene.hpp"

namespace Toya
{
	inline Components::GameObject* FindGameObject(const char* name)
	{
		for (auto o : SceneManagement::Scene::activeScene->SceneObjects)
		{
			if (std::strcmp(o->name, name) == 0) {
				return o;
			}
		}
		return nullptr;
	}

	inline void Destroy(Components::GameObject* object)
	{
		/*****************************************************************************************/
		//1- Collision
		CoreDrivers::CollisionManager::UnregisterObject(object->transform);
		//2- Renderer
		SceneManagement::Scene::activeScene->UnregisterObject(object->transform);
		/****************************************************************************************/
	}
	
}
