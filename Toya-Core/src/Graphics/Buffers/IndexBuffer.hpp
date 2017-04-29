#pragma once
#include <GLEW/GL/glew.h>

namespace Toya
{
	namespace Graphics
	{
		class IndexBuffer
		{
			GLuint m_BufferId;
			GLuint m_Count;
		public:
			IndexBuffer() = default;
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();
			void Bind() const;
			void Unbind() const;
			inline GLuint GetCount() const { return m_Count; }
		};

	}
}

