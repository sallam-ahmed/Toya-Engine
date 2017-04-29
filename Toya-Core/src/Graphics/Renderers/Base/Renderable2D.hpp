#pragma once
#include <GLM/glm.hpp>
#include "../../Buffers/Buffers.h"
#include "../../Shader.hpp"
#include "../../../Components/Base/RenderableComponent.hpp"

#define OLD 0
namespace Toya
{
	namespace Graphics
	{
		namespace Renderers {

		

			class Renderable2D : public Components::RenderableComponent
			{
			protected:
				glm::vec2 m_Size;
				glm::vec3 m_Position;
				glm::vec4 m_Color;
			public:
				Renderable2D() = default;
				Renderable2D(glm::vec3 pos, glm::vec2 size, glm::vec4 color) :
				m_Size(size), m_Position(pos), m_Color(color)
				{}

				virtual ~Renderable2D()
				{}

				inline glm::vec3 GetPosition() const { return m_Position; }
				inline glm::vec2 GetSize() const { return m_Size; }
				inline glm::vec4 GetColor() const { return m_Color; }
			};

		}
	}
}
