#pragma once
#include "../Math/Math.hpp"
#include "Color.hpp"
#include <vector>
#include "../Graphics/Textures/TextureLoader.hpp"

namespace Toya
{
	namespace CoreDrivers
	{
#define CUBEMAP_FRONT "res/SkyBox/front.tga"
#define CUBEMAP_BACK "res/SkyBox/back.tga"
#define CUBEMAP_TOP "res/SkyBox/top.tga"

#define CUBEMAP_BOTTOM "res/SkyBox/bottom.tga"
#define CUBEMAP_LEFT "res/SkyBox/left.tga"
#define CUBEMAP_RIGHT "res/SkyBox/right.tga"

#define SKYBOX_VERT_SHADER "Shaders/SkyBox/SkyBoxVertShader.glsl"
#define SKYBOX_FRAG_SHADER "Shaders/SkyBox/SkyBoxFragShader.glsl"

		class Lighting
		{
			static float m_AmbientIntensityMultiplier;
			static glm::vec4 m_AmbientColor;
			static Graphics::Shader *m_SkyBoxShader;
			
			static GLuint skyboxVAO, skyboxVBO;
			
			static GLfloat *skyboxVertices;
		public:
			static Graphics::CubeMap* SkyBox;
			Lighting()
			{
				
				m_AmbientIntensityMultiplier = 1.0f;
				m_AmbientColor = Color::Red;
			
			}
			static inline void SetAmbientColor(const glm::vec4& ambientColor) 
			{
				m_AmbientColor = ambientColor;
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
				m_SkyBoxShader = new Graphics::Shader(SKYBOX_VERT_SHADER, SKYBOX_FRAG_SHADER);
			
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
			//	ShaderManager::GetActiveShader()->Disable();
				m_SkyBoxShader->Enable();
				glDepthFunc(GL_LEQUAL);
				//glDepthMask(GL_FALSE);//Remember to turn depth writing off
				auto viewMatrixV = Matrix4x4(glm::mat4(glm::mat3(*Components::Camera::main->GetWorldToViewMatrix().GetGlm())));
				auto projectionMatrixV = Components::Camera::main->GetProjcetionMatrix();
				m_SkyBoxShader->SetUniformMat4("_viewMatrix", viewMatrixV);
				m_SkyBoxShader->SetUniformMat4("_projectionMatrix", projectionMatrixV);
				// skybox cube
				glBindVertexArray(skyboxVAO);
				glActiveTexture(GL_TEXTURE0);
				m_SkyBoxShader->SetUniform1i("skybox", 0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox->TextureId);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glDepthFunc(GL_LESS);
			//	fprintf(stdout, "RENDER CYCLE:: SkyBox Finished\n");
			}
		};
		Graphics::CubeMap *Lighting::SkyBox;
		GLuint Lighting::skyboxVAO;
		GLuint Lighting::skyboxVBO;
		Graphics::Shader *Lighting::m_SkyBoxShader;
	}
}
