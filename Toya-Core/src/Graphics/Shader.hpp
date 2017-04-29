#pragma once
#include <GLEW/GL/glew.h>
#include "../Utils/FileUtils.hpp"
#include "../Math/Math.hpp"


using namespace Toya::Math;

using namespace Toya::Utils;
namespace Toya
{
	namespace Graphics
	{
		class Shader
		{
		private:
			const char *m_VertexShaderPath, *m_FragShaderPath;
			GLuint m_ProgramId;
			static bool m_Initialized;
			//Shader* self;
		public:
			Shader() = default;
			Shader(const char* vertexShader, const char* fragemntShader);
			~Shader();
			void Enable() const;
			void Disable() const;
			
			GLuint GetProgramId() const;
			GLint _getUniformLocation(const GLchar* name) const;

			void SetUniformMat4(const GLchar* name, const Math::Matrix4x4)const;
			void SetUniform1f(const GLchar* name, const float value)const;
			
			void SetUniform2f(const GLchar* name, const glm::vec2 value)const;
			void SetUniform3f(const GLchar* name, const glm::vec3 value)const;
			void SetUniform4f(const GLchar* name, const glm::vec4 value)const;
			
			void SetUniform1i(const GLchar* name, const int value) const;

			static bool IsReady() { return m_Initialized; }
		private:
			GLuint _loadShader() const;
		};
#if 0
		class ShaderManager
		{
		public:
			ShaderManager() = default;
			static Shader* m_ActiveShader;
			inline static void SetActiveShader(Shader* sh)
			{
				m_ActiveShader = sh;
			}
			inline static Shader* GetActiveShader()
			{
				return m_ActiveShader;
			}
		};

#endif

	}
}


