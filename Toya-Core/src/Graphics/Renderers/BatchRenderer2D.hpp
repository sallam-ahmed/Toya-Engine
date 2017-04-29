#pragma once
#include "Base/Renderer2D.hpp"
#include "../Buffers/Buffers.h"
#include "Base/VertexData.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{
#define RENDERER_MAX_SPRITES  60000
#define RENDERER_VERTEX_SIZE  sizeof(VertexData)
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE  * 4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE  * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES  * 6
#define SHADER_VERTEX_INDEX 0

#define BUFFER_OFFSET(i) ((GLvoid*)i)
//#define SHADER_VERTEX_INDEX 0 NORMALS
//TEXIDS
#define SHADER_COLOR_INDEX 1
			class BatchRenderer2D : public Renderer2D
			{
				GLuint m_VAO;
				IndexBuffer *m_IBO;
				GLuint m_VBOId;
				GLsizei m_IndexCount;
				VertexData* m_Buffer;
			public:
				BatchRenderer2D();
				virtual ~BatchRenderer2D();
				void Submit(const Renderable2D* renderable2_d) override;
				void Flush() override;
				void Begin();
				void End();
			private:
				void _init();
			};

		}
	}
}

	