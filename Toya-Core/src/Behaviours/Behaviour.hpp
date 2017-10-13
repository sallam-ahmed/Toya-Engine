#pragma once
#include "../Components/Base/Transform.hpp"
namespace Toya
{
	namespace Behaviours
	{
		class Behaviour
		{
			friend class CollisionManager;
			virtual void _onCollision(Components::Transform* other, bool state);
		public:
			Behaviour();
			void ToggleEnable(bool enable);
			virtual void Start() = 0;
			virtual void Update() = 0;
			virtual void OnEnable() = 0;
			virtual ~Behaviour() = default;
			virtual void OnCollision(Components::Transform* other);
			virtual void OnCollisionExit(Components::Transform* other);
			
			Components::Transform* _lastCollision;
			GameObject* gameObject;
			bool _collided;
			bool enabled;
		};
	}
}
