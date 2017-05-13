#pragma once
#include <string>
#include <GL/glew.h>
#include "GLM/glm.hpp"
#include <map>
#include "../Shader.hpp"

namespace Toya
{
	namespace Graphics
	{
		 
#define TEXT_VS_SHADER   "Shaders/Default/TextVertShader.glsl"
#define TEXT_FRAG_SHADER "Shaders/Default/TextFragShader.glsl"
		struct Character
		{
			GLuint TextureID;   
			glm::ivec2 Size;    
			glm::ivec2 Bearing; 
			GLuint Advance;     
		};
		class TextRenderer
		{

		public:
			static void RenderText(float x, float y, std::string text, float scale, glm::vec4 color);
			static void LoadFont(std::string fontPath, GLuint fontSize);
			static std::map<GLchar, Character> FontCharacters;
			static void Init();
		private:
			static GLuint VAO, VBO;
			static Shader* TextShader;

		};
	}
}
