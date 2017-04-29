#include "BatchRenderer2D.hpp"
namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{

			BatchRenderer2D::BatchRenderer2D()
			{
				_init();
			}


			BatchRenderer2D::~BatchRenderer2D()
			{
				delete m_IBO;
				glDeleteBuffers(1, &m_VBOId);
			}


			void BatchRenderer2D::_init()
			{
				
				glGenVertexArrays(1, &m_VAO);
				glGenBuffers(1, &m_VBOId);
				
				glBindVertexArray(m_VAO);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);
				glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
				glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
				glEnableVertexAttribArray(SHADER_COLOR_INDEX);
				glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, BUFFER_OFFSET(0));
				glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, BUFFER_OFFSET((3 * sizeof(GLfloat))));
				
				//Clear Buffer
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
				int offset = 0;
				for (auto i = 0; i <RENDERER_INDICES_SIZE;i+=6)
				{
					indices[  i  ] = offset + 0;
					indices[i + 1] = offset + 1;
					indices[i + 2] = offset + 2;

					indices[i + 3] = offset + 2;
					indices[i + 4] = offset + 3;
					indices[i + 5] = offset + 0;

					offset += 4;
				}
				m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
				glBindVertexArray(0);
				
			}

			void BatchRenderer2D::Begin()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);
				m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			}
			void BatchRenderer2D::Submit(const Renderable2D* renderable2_d)
			{
				const glm::vec3& pos = renderable2_d->GetPosition();
				const glm::vec4& clr = renderable2_d->GetColor();
				const glm::vec2& size = renderable2_d->GetSize();

				m_Buffer->vPosition = pos;
				m_Buffer->vColor = clr;
				m_Buffer++;

				m_Buffer->vPosition = glm::vec3(pos.x, pos.y + size.y, pos.z);
				m_Buffer->vColor = clr;
				m_Buffer++;

				m_Buffer->vPosition = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
				m_Buffer->vColor = clr;
				m_Buffer++;

				m_Buffer->vPosition = glm::vec3(pos.x + size.x, pos.y, pos.z);
				m_Buffer->vColor = clr;
				m_Buffer++;

				m_IndexCount += 6;
			}
			void BatchRenderer2D::End()
			{
				glUnmapBuffer(GL_ARRAY_BUFFER);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void BatchRenderer2D::Flush()
			{
				glBindVertexArray(m_VAO);
				m_IBO->Bind();
				glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
				m_IBO->Unbind();
				glBindVertexArray(0);
				m_IndexCount = 0;
			}
		}
	}
}
