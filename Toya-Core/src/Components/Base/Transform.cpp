#include "Transform.hpp"


namespace Toya
{
	namespace Components
	{
		//glm::quat(cos(glm::radians(90.0f / 2)), 0, sin(glm::radians(90.0f / 2)) * 1, 0);
		//Transform *Transform::Self;

		Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale)
		{
			Self = this;
			Position = pos;
			Rotation = rot;
			Scale = scale;
			m_HasRenderer = false;
		}
		//Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale,GameObject *parnet_object)
		//{
 	//		Self = this;
		//	//ParentObject = parnet_object;
		//	Position = pos;
		//	Rotation = rot;
		//	Scale = scale;
		//	name = "Transform";
		//	m_HasRenderer = false;
		//}

		Transform::~Transform()

		{
			Self = nullptr;
			delete Self;
		}
		Component* Transform::AddComponent(Component* component)
		{
			if (std::strcmp(typeid(*component).name(), typeid(Graphics::Renderers::Sprite).name())== 0)
			{
				if (!m_HasRenderer) {
					SetRenderer(static_cast<Graphics::Renderers::Renderable2D*>(component));
					fprintf(stdout, "Renderer added for %s\n",gameObject->name);
					m_HasRenderer = true;
				}
				else
				{
					fprintf(stderr, "Transform -%s- already has renderer of type {%s} set!\n", gameObject->name, typeid(*component).name());
					return nullptr;
				}
			}
			component->transform = this;
			components.push_back(component);
			return component;
		}
		/*template <class T>
		T* Transform::GetComponent() 
		{ 
			for(Component* c : components)
			{
				if(typeid(c).name() == typeid(T).name())
				{
					return static_cast<T*>(c);
				}
			}
			return nullptr;
		}*/

		void Transform::Translate(const glm::vec3& axis, glm::vec3 amount)
		{
			this->Position += axis * amount;
		}
		void Transform::Translate(const glm::vec3& axis, float amount)
		{
			this->Position += axis * amount;
		}

		void Transform::Rotate(const glm::vec3 axis, float amount)
		{
			Rotation = glm::angleAxis(amount, axis);
		}
		void Transform::ScaleTransform(const glm::vec3& axis, glm::vec3 amount)
		{
			this->Scale += axis * amount;
		}
		Matrix4x4 Transform::GetModelMatrix() const
		{
			glm::mat4 glm_translate = glm::translate(glm::mat4(1.0), Position);
			glm::mat4 glm_rotate = glm::mat4_cast(Rotation);
			glm::mat4 glm_scale = glm::scale(glm::mat4(1.0), Scale);
			return Matrix4x4(glm_rotate * glm_scale * glm_translate);;
		}
	}
}
