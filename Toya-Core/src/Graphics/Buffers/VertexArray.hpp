#pragma once
#include <GLEW/GL/glew.h>
#include <vector>
#include "Buffer.hpp"

namespace Toya {
	namespace Graphics {
		class VertexArray
		{
			GLuint m_ArrayId;
			std::vector<Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer* buffer,GLuint index);
			void Bind() const;
			void Unbind() const;

		};
	}

}
