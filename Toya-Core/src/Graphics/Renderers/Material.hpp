#pragma once
#include "../../CoreDrivers/Color.hpp"
#include "../Shader.hpp"

namespace Toya
{
	namespace Graphics
	{
		struct Material
		{
			GLfloat Shininess;	
			
			CoreDrivers::Color TintColor = CoreDrivers::Color(1.0f, 1.0f, 1.0f,1.0f);
	
			Texture2D* DiffuseMap;
			Texture2D* SpecularMap;

			Material()
			{
				Shininess = 13.0f;
				DiffuseMap = SpecularMap = nullptr;
			}
		};
	}
}