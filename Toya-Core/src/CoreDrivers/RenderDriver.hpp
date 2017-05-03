#pragma once
#include <vector>
#include "Lighting.hpp"

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
				}
				Lighting::RenderSkyBox();

				Components::Camera::main->UpdateViewMatrix();

				auto viewMatrix = Components::Camera::main->GetWorldToViewMatrix();
				auto projectionMatrix = Components::Camera::main->GetProjcetionMatrix();
				ShaderManager::GetActiveShader()->SetUniformMat4("_viewMatrix", viewMatrix);
				ShaderManager::GetActiveShader()->SetUniformMat4("_projectionMatrix", projectionMatrix);
			}
			
		};
	}
}
