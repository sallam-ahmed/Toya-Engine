#include "Material.hpp"

namespace Toya
{
	namespace  Graphics
	{
		using namespace CoreDrivers;
		Material::Material()
		{
			tintColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
			shininess = 13.0f;
			diffuseMap = nullptr;
			specularMap = nullptr;
			shader = ShaderManager::LoadShader(DEFAULT_MODEL_VERT_SHADER, DEFAULT_MODEL_FRAG_SHADER);
		}

		Material::~Material()
		{
			//pass
		}

		void Material::Render()
		{
			shader->Enable();
			//pass uniforms to shader
		}
	}
}