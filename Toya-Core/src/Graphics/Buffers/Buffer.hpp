#pragma once
#include <GLEW/GL/glew.h>

namespace Toya
{
	namespace Graphics
	{
		class Buffer
		{
			GLuint m_BufferId;
			GLuint m_ComponentCount;
		public:
			Buffer() = default;
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();
			void Bind() const;
			void Unbind() const;
			inline GLuint GetComponentCount() const { return m_ComponentCount; }
		};
	}
}
