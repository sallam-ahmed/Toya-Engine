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
			//	Lighting::LightingInit();
			}
			static void RenderUpdateLoop()//std::vector<Components::Transform*> renderers)
			{
				//Render Sky Box Last for performance
				Lighting::RenderSkyBox();
			}
			static void RenderUpdateLoop(std::vector<Components::Model*> models)
			{
			//	auto olShader = ShaderManager::GetActiveShader();

				for (auto mdl : models)
					mdl->Render();

				//olShader->Enable();
				Lighting::RenderSkyBox();
			}
		};
	}
}
