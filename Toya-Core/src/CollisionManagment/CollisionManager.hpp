#pragma once
#include <vector>
#include "../Components/Base/Transform.hpp"
#include "../Math/AABB.h"
namespace Toya
{
	namespace CoreDrivers
	{

	class CollisionManager
	{
		static std::vector<Toya::Components::Transform*> Collidables;
	public:
		CollisionManager();
		~CollisionManager();
		static void AddListener(Components::Transform* listener);
		static void CollisionUpdateLoop();
		static void UnregisterObject(Components::Transform* obj);


	};

		
	}
}
