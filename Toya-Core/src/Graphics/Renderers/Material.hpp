#pragma once
#include "../Shader.hpp"
#include "../../CoreDrivers/Color.hpp"

namespace Toya
{
	namespace Graphics
	{
		class Material
		{
			friend class Shader;
		public:
			GLfloat shininess;	
			
			CoreDrivers::Color tintColor;
			
			Texture2D* diffuseMap;
			Texture2D* specularMap;
			
			Shader* shader;
			
			Material();
			
			virtual ~Material();
			
			void Render();
		};
	}
}
