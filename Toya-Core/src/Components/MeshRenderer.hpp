#pragma once
#include "Mesh.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Renderers/Material.hpp"

namespace Toya
{
	namespace Components
	{
		class MeshRenderer : public RenderableComponent
		{
		public:
			std::vector<Mesh*> Meshes;
			Material* RenderMaterial;
			MeshRenderer() = default;
			explicit MeshRenderer(Material* mat)
			{
				//Init
				RenderMaterial = mat;
			}

			void Render() const
			{
				
			}
		};
	}
}
