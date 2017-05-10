#include "Transform.hpp"
#include "../BoxCollider.hpp"
#include <GLM/detail/type_mat.hpp>
#include <GLM/detail/type_mat.hpp>
#include "../../CollisionManagment/CollisionManager.hpp"

namespace Toya
{
	namespace Components
	{
		Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale)
		{
			Self = this;
			Position = pos;
			Rotation = rot;
			Scale = scale;
			m_HasRenderer = false;
		}
		Transform::~Transform()

		{
			Self = nullptr;
			delete Self;
		}
		Component* Transform::AddComponent(Component* component)
		{
			component->transform = this;
			
			components.push_back(component);
			
			return component;
		}

		void Transform::LookAt(glm::vec3& to_vector)
		{
			auto f = glm::normalize(this->Position);
			auto t = glm::normalize(to_vector);
			float cosa = glm::dot(f, t);
			glm::clamp(cosa, -1.0f, 1.0f);
			glm::vec3 axis = glm::cross(f, t);
			float angle = glm::degrees(glm::acos(cosa));

			Rotation = glm::angleAxis(angle,axis);
		}

		void Transform::Translate(const glm::vec3& axis, glm::vec3 amount)
		{
			auto col = static_cast<BoxCollider*>(GetComponent<BoxCollider>());
			this->Position += axis * amount;
			GetModelMatrix();
			Toya::CoreDrivers::CollisionManager::CollisionUpdateLoop();

			if (col != nullptr)
			{
				if (!col->Free)
				{
					this->Position -= axis * amount;
				}
			}

		}
		void Transform::Translate(const glm::vec3& axis, float amount)
		{
			auto col = static_cast<BoxCollider*>(GetComponent<BoxCollider>());
			this->Position += axis * amount;
			GetModelMatrix();
			Toya::CoreDrivers::CollisionManager::CollisionUpdateLoop();
			
			if (col != nullptr)
			{
				if (!col->Free)
				{
					this->Position -= axis * amount;
				}
			}
		}

		void Transform::Rotate(const glm::vec3 axis, float amount)
		{
			auto col = static_cast<BoxCollider*>(GetComponent<BoxCollider>());
			Rotation *= glm::angleAxis(glm::radians(amount), axis);
			GetModelMatrix();
			Toya::CoreDrivers::CollisionManager::CollisionUpdateLoop();

			if (col != nullptr)
			{
				if (!col->Free)
					Rotation *= glm::angleAxis(glm::radians(amount), -axis);
			}
		}
		void Transform::ScaleTransform(const glm::vec3& axis, glm::vec3 amount)
		{
			auto col = static_cast<BoxCollider*>(GetComponent<BoxCollider>());
			this->Scale += axis * amount;
			GetModelMatrix();
			CoreDrivers::CollisionManager::CollisionUpdateLoop();

			if (col != nullptr)
			{
				if (!col->Free)
					this->Scale -= axis * amount;
			}
		}
		glm::mat4 Transform::GetModelMatrix()
		{
			glm::mat4 glm_translate = glm::translate(glm::mat4(1.0), Position);
			glm::mat4 glm_rotate = glm::mat4_cast(Rotation);
			glm::mat4 glm_scale = glm::scale(glm::mat4(1.0), Scale);
			auto mt = glm_translate * glm_rotate * glm_scale;
			
			auto col = static_cast<BoxCollider*>(GetComponent<BoxCollider>());
			if (col != nullptr)
				col->GetBoundingBox()->TransformAABB(mt);

			return glm_translate * glm_rotate * glm_scale;
		}
	}
}
