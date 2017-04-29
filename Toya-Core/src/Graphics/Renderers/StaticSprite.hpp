#pragma once
#include "Base/Renderable2D.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{
			class StaticSprite : public Renderable2D
			{
				VertexArray *m_VertexArray;
				IndexBuffer *m_IndexBuffer;
				Shader& m_Shader;
			public:
				StaticSprite(float x, float y, float width, float height, glm::vec4 color, Shader& shader);
				StaticSprite(const glm::vec3 &pos, const glm::vec2& size, glm::vec4 color, Shader& shader);
				StaticSprite() = default;
				~StaticSprite();
				
				inline  VertexArray* GetVAO() const { return m_VertexArray; };
				inline  IndexBuffer* GetIBO() const { return m_IndexBuffer; };
				inline	Shader& GetShader() const { return m_Shader; }
			};

		}
	}
}
