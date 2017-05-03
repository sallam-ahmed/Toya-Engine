#pragma once
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include "../../Math/Math.hpp"
#include <vector>
#include "../../Graphics/Renderers/Base/Renderable2D.hpp"
#include "../../Graphics/Renderers/Sprite.hpp"
#include "Component.hpp"


using namespace Toya::Math;
using namespace Toya::Graphics::Renderers;
namespace Toya
{
	namespace Components
	{
		class GameObject;
		class Behaviour;
		class Behaviour : public Component
		{
		public:
			Behaviour() { gameObject = nullptr; enabled = true; }
			virtual void Start() = 0;
			virtual void Update() = 0;
			GameObject* gameObject;
			bool enabled;
		};
		class Transform
		{
			glm::mat4 m_TranslationMatrix;
			glm::mat4 m_ScaleMatrix;
			glm::mat4 m_RotationMatrix;
			bool m_HasRenderer;
			Renderable2D *m_Rendererable;
		protected:
			Transform* Self;
			Transform* Parent;
		public:
			explicit Transform(const glm::vec3& pos = glm::vec3(0.0), const glm::quat& rot = glm::quat(1.0, 0.0, 0.0, 0.0), const glm::vec3& scale = glm::vec3(1.0));
			///explicit Transform(const glm::vec3& pos , const glm::quat& rot , const glm::vec3& scale , GameObject* parnet_object );
			~Transform();
			inline Renderable2D* GetRenderer() const { return m_Rendererable; }
			inline void SetRenderer(Renderable2D *rendererable2D) { m_Rendererable = rendererable2D; }
			inline Behaviour* Attach(Behaviour* behaviour)
			{
				behaviour->gameObject = gameObject;
				behaviour->transform = this;
				Behaviours.push_back(behaviour);
				return behaviour;
			}
			std::vector<Behaviour*> Behaviours;
			GameObject *gameObject;
			glm::vec3 Position;
			glm::vec3 Scale;
			glm::quat Rotation;

			std::vector<Component*> components;
			
			void Translate(const glm::vec3& axis,glm::vec3 amount);
			void Translate(const glm::vec3& axis, float amount);
			void Rotate(const glm::vec3 axis, float amount);
			void ScaleTransform(const glm::vec3& axis,glm::vec3 amount);
			Component* AddComponent(Component* cmp);
			template <class T>
			inline T* GetComponent(){
				for (auto c : components)
				{
				//	fprintf(stdout, "1-> %s\n2->%s\n",typeid(c).name(),typeid(T).name());
					if (dynamic_cast<T*>(c))
					{
						return static_cast<T*>(c);
					}
				}
				return nullptr;
			}
			template <class T >
			inline T* GetBehaviour()
			{
				for (auto c : Behaviours)
				{
					//	fprintf(stdout, "1-> %s\n2->%s\n",typeid(c).name(),typeid(T).name());
					if (dynamic_cast<T*>(c))
					{
						return static_cast<T*>(c);
					}
				}
				return nullptr;
			}
			Matrix4x4 GetModelMatrix() const;

			virtual Transform* GetTransform()const { return Self; }

		};
		class GameObject
		{
			
		public:
			GameObject() :name("GameObject"), tag("Untagged"), transform(new Transform())
			{
				transform->gameObject = this;
			};
			char* name;
			char* tag;
			Transform* transform;

		};
		#if 0
		struct Transform
		{
			glm::mat4 m_TranslationMatrix;
			glm::mat4 m_ScaleMatrix;
			glm::mat4 m_RotationMatrix;
			bool m_HasRenderer;
			Renderable2D *m_Rendererable;
		protected:
			Transform* Self;
			Transform* Parent;

		public:
			explicit Transform(const glm::vec3& pos = glm::vec3(0.0), const glm::quat& rot = glm::quat(1.0, 0.0, 0.0, 0.0), const glm::vec3& scale = glm::vec3(1.0));
			///explicit Transform(const glm::vec3& pos , const glm::quat& rot , const glm::vec3& scale , GameObject* parnet_object );
			//~Transform();
			
			inline Renderable2D* GetRenderer() const
			{
				return m_Rendererable;
			}
			inline void SetRenderer(Renderable2D *rendererable2D)
			{
				m_Rendererable = rendererable2D;
			}

			glm::vec3 Position;
			glm::vec3 Scale;
			glm::quat Rotation;

			std::vector<Component*> components;
			char* name;

			void Translate(const glm::vec3& axis, glm::vec3 amount)
			{
				
			}
			void Translate(const glm::vec3& axis, float amount)
			{
				
			}
			void Rotate(const glm::vec3 axis, float amount)
			{
				
			}
			void ScaleTransform(const glm::vec3& axis, glm::vec3 amount)
			{
				
			}
			void AddComponent(Component* cmp)
			{
				
			}

			template <class T>
			inline T* GetComponent() {
				for (auto c : components)
				{
					//	fprintf(stdout, "1-> %s\n2->%s\n",typeid(c).name(),typeid(T).name());
					if (dynamic_cast<T*>(c))
					{
						return static_cast<T*>(c);
					}
				}
				return nullptr;
			}

			Matrix4x4 GetModelMatrix() const
			{
				
			}
			virtual Transform* GetTransform()const
			{
				return Self;
			}
		};

#endif
	}
}
