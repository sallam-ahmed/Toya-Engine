#pragma once
#include <deque>
#include "Base/Renderable2D.hpp"
#include "Base/Renderer2D.hpp"
#include "StaticSprite.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers {
			class Simple2DRenderer : public Renderer2D
			{
				std::deque<const StaticSprite*> m_RenderQueue;
			public:
				void Submit(const Renderable2D* renderable) override;
				void Flush() override;
			private:

			};
		}
	}
}
