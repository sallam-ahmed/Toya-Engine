#include "GameObject.hpp"
namespace Toya
{
	GameObject::GameObject() : 
	name("GameObject"), tag("Untagged"), transform(new Components::Transform())
	{
		transform->gameObject = this;
	}
}
