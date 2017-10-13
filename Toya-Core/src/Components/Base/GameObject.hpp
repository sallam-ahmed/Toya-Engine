#pragma once
#include "Transform.hpp"

namespace Toya
{
	class GameObject
	{
	public:
		GameObject();
		char* name;
		char* tag;
		Components::Transform* transform;
	};
}
