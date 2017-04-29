#pragma once
#include "Renderable2D.hpp"

namespace Toya
{
	namespace Graphics
	{
		namespace Renderers {
			class Renderer2D
			{
			protected:
				virtual void Submit(const Renderable2D* renderable) = 0;
				virtual void Flush() = 0;
			public:
				virtual ~Renderer2D();

			};

			inline Renderer2D::~Renderer2D()
			{
			}
		}

	}
}
