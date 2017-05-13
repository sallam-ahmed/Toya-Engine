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
			virtual void Start(){}
			virtual void Update(){}
			virtual void OnEnable(){}
		};

	}
}

