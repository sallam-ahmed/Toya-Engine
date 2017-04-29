#include "Simple2DRenderer.hpp"


namespace Toya
{
	namespace Graphics
	{
		namespace Renderers {
			void Simple2DRenderer::Submit(const Renderable2D* renderable)
			{
				m_RenderQueue.push_back(static_cast< const StaticSprite*>(renderable));
			}

			void Simple2DRenderer::Flush()
			{

				while (!m_RenderQueue.empty())
				{
					auto renderable = m_RenderQueue.back();
					renderable->GetVAO()->Bind();
					renderable->GetIBO()->Bind();
					renderable->GetShader().SetUniformMat4("_modelMatrix", Matrix4x4(glm::translate(renderable->GetPosition())));

					glDrawElements(GL_TRIANGLES, renderable->GetIBO()->GetCount(), GL_UNSIGNED_SHORT, NULL);
					renderable->GetIBO()->Unbind();
					renderable->GetVAO()->Unbind();
					m_RenderQueue.pop_back();
				}
			}
		}
	}
}
