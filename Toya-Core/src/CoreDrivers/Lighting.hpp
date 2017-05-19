#pragma once
#include "../Math/Math.hpp"
#include "Color.hpp"
#include <vector>
#include "../Graphics/Textures/TextureLoader.hpp"
#include "../Components/Light/Light.hpp"
#include "Base/IManager.hpp"


namespace Toya
{
	namespace CoreDrivers
	{
#if 0
#define CUBEMAP_FRONT "res/SkyBox/front.tga"
#define CUBEMAP_BACK "res/SkyBox/back.tga"
#define CUBEMAP_TOP "res/SkyBox/top.tga"

#define CUBEMAP_BOTTOM "res/SkyBox/bottom.tga"
#define CUBEMAP_LEFT "res/SkyBox/right.tga"
#define CUBEMAP_RIGHT "res/SkyBox/left.tga"

#endif

#define CUBEMAP_FRONT "res/SkyBox/DeepSpace/front.png"
#define CUBEMAP_BACK "res/SkyBox/DeepSpace/back.png"

#define CUBEMAP_TOP "res/SkyBox/DeepSpace/top.png"
#define CUBEMAP_BOTTOM "res/SkyBox/DeepSpace/bottom.png"

#define CUBEMAP_LEFT "res/SkyBox/DeepSpace/left.png"
#define CUBEMAP_RIGHT "res/SkyBox/DeepSpace/right.png"


#define SKYBOX_VERT_SHADER "Shaders/SkyBox/SkyBoxVertShader.glsl"
#define SKYBOX_FRAG_SHADER "Shaders/SkyBox/SkyBoxFragShader.glsl"

		class Lighting 
		{
			static float m_AmbientIntensityMultiplier;
			static Graphics::Shader *m_SkyBoxShader;
			
			static GLuint skyboxVAO, skyboxVBO;
			
			static GLfloat *skyboxVertices;
			static int _lightCount;
			static std::vector<GamePlay::Light*> sceneLights;
		public:
			static Graphics::CubeMap* SkyBox;
			static Color AmbientColor;

			Lighting()
			{
				_lightCount = 0;
				m_AmbientIntensityMultiplier = 1.0f;
				AmbientColor = Color(1,0,0,1);
			}

			static void RegisterLight(GamePlay::Light* light)
			{
				sceneLights.push_back(light);
			}
			static int GetNextLightIndex()
			{
				return _lightCount++;
			}

			static inline void SetAmbientColor(const glm::vec4& ambientColor) 
			{
				AmbientColor = ambientColor;
			}
			static inline void LoadSkyBox()
			{
				SkyBox = new Graphics::CubeMap();
				SkyBox->texture_faces.push_back(CUBEMAP_RIGHT);
				SkyBox->texture_faces.push_back(CUBEMAP_LEFT);
				
				SkyBox->texture_faces.push_back(CUBEMAP_TOP);
				SkyBox->texture_faces.push_back(CUBEMAP_BOTTOM);

				SkyBox->texture_faces.push_back(CUBEMAP_FRONT);
				SkyBox->texture_faces.push_back(CUBEMAP_BACK);
				
				SkyBox->TextureId = -1;
				
				Graphics::TextureLoader::LoadCubeMapTexture(SkyBox);
				
				m_SkyBoxShader = ShaderManager::LoadShader(SKYBOX_VERT_SHADER, SKYBOX_FRAG_SHADER);
			}
			static inline void LightingInit()
			{
				GLfloat skyboxVertices[] = {
					// Positions          
						-1.0f, 1.0f, -1.0f,
						-1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,

						-1.0f, -1.0f, 1.0f,
						-1.0f, -1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f, -1.0f, 1.0f,

						1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,

						-1.0f, -1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, -1.0f, 1.0f,
						-1.0f, -1.0f, 1.0f,

						-1.0f, 1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, -1.0f,

						-1.0f, -1.0f, -1.0f,
						-1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,
						-1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, 1.0f
				};
				glGenVertexArrays(1, &skyboxVAO);
				glGenBuffers(1, &skyboxVBO);
				glBindVertexArray(skyboxVAO);
				glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			}
			static inline void RenderSkyBox()
			{
				m_SkyBoxShader->Enable();
				glDepthFunc(GL_LEQUAL);
				auto viewMatrixV = glm::mat4(glm::mat3(*Components::Camera::main->GetWorldToViewMatrix()));
				auto projectionMatrixV = *Components::Camera::main->GetProjcetionMatrix();
				m_SkyBoxShader->SetUniformMat4("_viewMatrix", viewMatrixV);
				m_SkyBoxShader->SetUniformMat4("_projectionMatrix", projectionMatrixV);
				glBindVertexArray(skyboxVAO);
				glActiveTexture(GL_TEXTURE0);
				m_SkyBoxShader->SetUniform1i("skybox", 0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox->TextureId);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glDepthFunc(GL_LESS);
			}
			static inline void RenderLights()
			{
				ShaderManager::GetActiveShader()->SetUniform1i("LightCount", sceneLights.size() - 1); //Exclude the directional light
				ShaderManager::GetActiveShader()->SetUniform4f("ambientColor",*(AmbientColor.GetGlm()) * m_AmbientIntensityMultiplier);
				ShaderManager::GetActiveShader()->SetUniform3f("viewPos", Components::Camera::main->transform->Position);
				for (auto i = 0; i < sceneLights.size(); i++)
				{
					sceneLights[i]->Update();
				}
			}
		};
		Graphics::CubeMap *Lighting::SkyBox;
		GLuint Lighting::skyboxVAO;
		GLuint Lighting::skyboxVBO;
		int Lighting::_lightCount = 0;
		Color Lighting::AmbientColor = Color(.3f,.3f,.3f,1.0f);
		Graphics::Shader *Lighting::m_SkyBoxShader;
		std::vector<GamePlay::Light*> Lighting::sceneLights;
		float Lighting::m_AmbientIntensityMultiplier = 1.0f;
	}
}
