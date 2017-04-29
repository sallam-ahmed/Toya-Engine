#pragma once
#include "GLM/glm.hpp"
namespace Toya
{
	namespace Graphics
	{
		struct VertexData
		{
			glm::vec3 vPosition;
			
			glm::vec4 vColor;
		};
		
		struct ComplexVertex
		{
			glm::vec3 vPosition;
			//glm::vec4 vColor;
			glm::vec3 vNormals;
			glm::vec2 vTexCoords;
		};
	}
}
