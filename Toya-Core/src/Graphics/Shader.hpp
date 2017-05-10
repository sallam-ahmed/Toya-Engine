#pragma once
#include <GLEW/GL/glew.h>
#include "../Utils/FileUtils.hpp"
#include "../Math/Math.hpp"
#include <map>
#include "Textures/Texture2D.hpp"


using namespace Toya::Math;

using namespace Toya::Utils;
namespace Toya
{
	namespace Graphics
	{
#define DEFAULT_MODEL_VERT_SHADER "Shaders/Default/ModelDefVertShader.glsl"
#define DEFAULT_MODEL_FRAG_SHADER "Shaders/Default/ModelDefFragShader.glsl"
#define PRIMITIVE_DIFFUSE_TEXTURE "res/Primitives/primitive_diffuse.jpg"
		class ShaderManager;
		class Shader
		{
			friend class ShaderManager;
		private:
			const char *m_VertexShaderPath, *m_FragShaderPath;
			GLuint m_ProgramId;
			static bool m_Initialized;
			Shader* self;
			Shader() = default;
			Shader(const char* vertexShader, const char* fragemntShader);
		public:
			~Shader();
			void Enable() const;
			void Disable() const;
			
			GLuint GetProgramId() const;
			GLint _getUniformLocation(const GLchar* name) const;

			void SetUniformMat4(const GLchar* name, const glm::mat4&)const;
			void SetUniform1f(const GLchar* name, const float value)const;
			
			void SetUniform2f(const GLchar* name, const glm::vec2 value)const;
			void SetUniform3f(const GLchar* name, const glm::vec3 value)const;
			void SetUniform4f(const GLchar* name, const glm::vec4 value)const;
			
			void SetUniform1i(const GLchar* name, const int value) const;
			void SetUniformBool(const GLchar* name, const bool value) const;
			static bool IsReady() { return m_Initialized; }
		private:
			GLuint _loadShader() const;
		};
#if 1
		class ShaderManager
		{
			friend class Shader;
		
			static std::map<size_t, Shader*> m_ShaderBank;
			
		public:
			
			static std::map<GLuint, GLchar*> shaderMap;
			static Shader* m_ActiveShader;
			static Shader* DefaultModelShader; 
			static Texture2D* DefaultTexture; 

			inline static Shader* GetActiveShader()
			{
				return m_ActiveShader;
			}
			inline static void DrawPrimitive()
			{
				DefaultModelShader->Enable();
			}
			inline static bool IsLoaded(std::string vertShader, std::string fragShader)
			{
				return (m_ShaderBank[_getShaderHash(vertShader,fragShader)] != nullptr);
			}
			inline static Shader* LoadShader(std::string vertShaderPath,std::string fragShaderPath)
			{
				if (IsLoaded(vertShaderPath, fragShaderPath))
				{
					fprintf(stdout,"Shader Loaded Retrieve.\n");
					return m_ShaderBank[_getShaderHash(vertShaderPath, fragShaderPath)];
				}
				m_ShaderBank[_getShaderHash(vertShaderPath, fragShaderPath)] =
						new Shader(vertShaderPath.c_str(), fragShaderPath.c_str());
				
				return m_ShaderBank[_getShaderHash(vertShaderPath, fragShaderPath)];
			}
		private:
			ShaderManager() = default;
			inline static void SetActiveShader(Shader* sh)
			{
				//fprintf(stdout, "Current Active Shader %s\n", shaderMap[sh->GetProgramId()]);
				m_ActiveShader = sh;
			}
			inline static size_t _getShaderHash(std::string vert,std::string frag)
			{
				auto purePath = vert.substr(vert.find_last_of("/") + 1);
				purePath += frag.substr(frag.find_last_of("/") + 1);
				return _hash(purePath.c_str());
			}
		};
		

#endif

	}
}


