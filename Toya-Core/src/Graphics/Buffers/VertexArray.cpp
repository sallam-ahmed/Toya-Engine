#include "VertexArray.hpp"

namespace Toya
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayId);

		}


		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_Buffers.size(); i++)
			{
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ArrayId);
		}

		/**
		 * \brief 
		 * \param buffer Buffer that holds data
		 * \param index Shader Index in layout table 
		 */
		void Toya::Graphics::VertexArray::AddBuffer(Buffer* buffer, GLuint index)
		{
			Bind();
			buffer->Bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0);
			buffer->Unbind();
			Unbind();
			m_Buffers.push_back(buffer);
		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(m_ArrayId);
		}
		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}


	}
}
