#include "Behaviour.hpp"


namespace Toya
{
	namespace Behaviours
	{
		Behaviour::Behaviour()
		{
			gameObject = nullptr; enabled = true; _collided = false; _lastCollision = nullptr;
		}

		void Toya::Behaviours::Behaviour::_onCollision(Components::Transform* other, bool state)
		{
			_collided = state;
			_lastCollision = other;
			if (_collided)
			{
				OnCollision(other);
			}
			else
			{
				OnCollisionExit(other);
			}
		}

		void Behaviour::ToggleEnable(bool enable)
		{
			enabled = enable;
			if (enabled)OnEnable();
		}

		void Behaviour::OnCollision(Components::Transform* other)
		{
		}

		void Behaviour::OnCollisionExit(Components::Transform* other)
		{
		}
	}
}
