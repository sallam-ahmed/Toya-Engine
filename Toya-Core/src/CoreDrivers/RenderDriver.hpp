#pragma once
#include <vector>
#include "Lighting.hpp"
#include "../Graphics/Renderers/TextRenderer.hpp"

namespace Toya
{
	namespace CoreDrivers
	{
		class RenderManager
		{
		public:
			static void RenderInitialize()
			{
				Lighting::LoadSkyBox();
				Lighting::LightingInit();
				TextRenderer::Init();
				TextRenderer::LoadFont("Fonts/times.ttf", 25);
			}
			static void RenderUpdateLoop()
			{
				Lighting::RenderSkyBox();
				
			}
			static void RenderUpdateLoop(std::vector<Components::Model*> models)
			{
				for(int i = 0; i < models.size();i++)
				{

					models[i]->Render();
					Lighting::RenderLights();
				}
				TextRenderer::RenderText(10, 10, "Hello", 5.0f, glm::vec4(1.0, 0.0f, 0.0f, 1.0f));
				Lighting::RenderSkyBox();
				Components::Camera::main->UpdateViewMatrix();
				auto viewMatrix = Components::Camera::main->GetWorldToViewMatrix();
				auto projectionMatrix = Components::Camera::main->GetProjcetionMatrix();
				ShaderManager::GetActiveShader()->SetUniformMat4("_viewMatrix", *viewMatrix);
				ShaderManager::GetActiveShader()->SetUniformMat4("_projectionMatrix", *projectionMatrix);
			}
			
		};
	}
}
