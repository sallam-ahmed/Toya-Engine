#include "Shader.hpp"
#include <vector>

#define ERROR_CHECK GLenum err = glGetError();if(err!=GL_NO_ERROR)fprintf(stderr,"ERROR-> %u\n",err);


namespace Toya
{
	namespace Graphics
	{
		bool Shader::m_Initialized = false;
		/*******************************************************************/
		std::map<GLuint, GLchar*> ShaderManager::shaderMap;
		Shader* ShaderManager::m_ActiveShader;
		Shader* ShaderManager::DefaultModelShader;
		Texture2D* ShaderManager::DefaultTexture;
		std::map<size_t, Shader*> ShaderManager::m_ShaderBank;
		/***********************************************************************/

		Shader::Shader(const char* vertexShader, const char* fragemntShader) 
		:m_VertexShaderPath(vertexShader), m_FragShaderPath(fragemntShader)
		{
			m_ProgramId = _loadShader();
			fprintf(stdout, "Shader Loaded Successfully of %s\n ID = %u\n",vertexShader,m_ProgramId);
			ShaderManager::shaderMap[m_ProgramId] = const_cast<GLchar*>(vertexShader);
			self = this;
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ProgramId);
		}

		void Shader::Enable() const
		{
			ShaderManager::SetActiveShader(self);
			glUseProgram(m_ProgramId);
		}

		void Shader::Disable() const
		{
			glUseProgram(0);
		}

		GLuint Shader::GetProgramId() const
		{
			return m_ProgramId;
		}

		GLint Shader::_getUniformLocation(const GLchar *name) const
		{
			//Todo Cache
			//GLenum err = glGetError(); if (err != GL_NO_ERROR)fprintf(stderr, "ERROR FROM GET BEFOR-> %u\n", err);

			auto m = glGetUniformLocation(m_ProgramId, name);
			//err = glGetError(); if (err != GL_NO_ERROR)fprintf(stderr, "ERROR AFTER-> %u\n", err);
			return m;
		}
		void Shader::SetUniformMat4(const GLchar* name, const glm::mat4& mat)const
		{

			auto n = _getUniformLocation(name);
			glUniformMatrix4fv(n, 1, GL_FALSE,glm::value_ptr(mat));
		}

		void Shader::SetUniform1f(const GLchar* name, const float value)const
		{
			glUniform1f(_getUniformLocation(name), value);
		}

		void Shader::SetUniform2f(const GLchar* name, const glm::vec2 value) const
		{
			glUniform2f(_getUniformLocation(name), value.x,value.y);
		}

		void Shader::SetUniform3f(const GLchar* name, const glm::vec3 value)const
		{
			glUniform3f(_getUniformLocation(name), value.x,value.y,value.z);
		}

		void Shader::SetUniform4f(const GLchar* name, const glm::vec4 value)const
		{
			glUniform4f(_getUniformLocation(name), value.x, value.y, value.z,value.w);
		}

		void Shader::SetUniform1i(const GLchar* name, const GLint value) const
		{
			glUniform1i(_getUniformLocation(name), value);
		}

		void Shader::SetUniformBool(const GLchar* name, const bool value) const
		{
			glUniform1i(_getUniformLocation(name), value ? 1 : 0);
		}

		GLuint Shader::_loadShader() const
		{
			auto programId = glCreateProgram();
			auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
			auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			auto vertexShaderSourceStr = read_file(m_VertexShaderPath);
			auto vertexShaderSource = vertexShaderSourceStr.c_str();
			
			auto fragmentShaderSourceStr = read_file(m_FragShaderPath);
			auto fragmentShaderSource = fragmentShaderSourceStr.c_str();
			
			glShaderSource(vertexShader, 1, &(vertexShaderSource), NULL);
			glCompileShader(vertexShader);

			GLint compileResult;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
			if (compileResult == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertexShader, length, &length, &error[0]);
				fprintf(stderr, "Failed to compile and run Vertex Shader\n %s\n",&error[0]);
				glDeleteShader(vertexShader);
				return 0;
			}
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
			if (compileResult == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);
				fprintf(stderr, "Failed to compile and run Fragment Shader\n %s\n", &error[0]);
				glDeleteShader(fragmentShader);
				system("pause");
				return 0;
			}

			glAttachShader(programId, vertexShader);
			glAttachShader(programId, fragmentShader);

			glLinkProgram(programId);
			glValidateProgram(programId);

			//Free up some memory
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			m_Initialized = true;
			return programId;
		}
	}
}
