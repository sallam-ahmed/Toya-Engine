#pragma once
namespace Toya
{

	namespace Components
	{
		class Transform;
		class Component
		{
		public:
			Component() = default;
			virtual ~Component() {}
			Transform* transform;
		};

	}
}

