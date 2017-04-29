#pragma once
#include "../../CoreDrivers/Color.hpp"
#include "../Shader.hpp"

namespace Toya
{
	namespace Graphics
	{
#define MATERIAL_VERTEX_SHADER "Shaders/MaterialShader/VertexShader.glsl"
#define MATERIAL_FRAGMENT_SHADER "Shaders/MaterialShader/FragmentShader.glsl"
		struct Material
		{
			float Shininess;	
			CoreDrivers::Color TintColor = CoreDrivers::Color(1.0f, 1.0f, 1.0f,1.0f);
			
			glm::vec3 Diffuse;
			glm::vec3 Specular;
			glm::vec3 AmbientReaction;
			
			char *VertexShader = MATERIAL_VERTEX_SHADER, *FragmentShader = MATERIAL_FRAGMENT_SHADER;

			Shader* ActiveShader;
			GLchar* ModelMatrixUniform = "_modelMatrix"; //Default Model Matix Unifrom Prop
			Material()
			{
				Shininess = 1.0f;
				ActiveShader = new Shader(VertexShader, FragmentShader);
			}
		};
	}
}
