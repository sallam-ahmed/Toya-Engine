#pragma once
#include "PlayerBehaviour.hpp"
#include "../CoreDrivers/Color.hpp"

namespace GamePlay
{
	class DirectionalLight : public Toya::Components::Behaviour
	{
		float diffuseFactor, specularFactor;
	public:
		Toya::CoreDrivers::Color* LightColor;
		DirectionalLight()
		{
			diffuseFactor = .5f;
			specularFactor = .7f;
			Intensity = 1.0f;
		}
		
		float Intensity;
		void Start() override
		{
			LightColor = new Toya::CoreDrivers::Color(.7f, .7f, .7f, 1.0f);

		}

		void Update() override
		{
			
		}
		void UpdateLoop()
		{
			_getShader()->SetUniform3f(_getAttrib("direction"), glm::vec3(-.2f, -.4f, 0.0f));
			_getShader()->SetUniform4f(_getAttrib("color"), glm::vec4(0.5f, .2f, .1f, 1.0f));
			_getShader()->SetUniform1f(_getAttrib("dFactor"), .5f);
			_getShader()->SetUniform1f(_getAttrib("sFactor"), .7f);
		}
		void OnEnable() override
		{
		}

	private:
		inline const GLchar* _getAttrib(std::string attribName) const
		{
			std::string qualifier = ("dirLight.");
			return (qualifier + attribName).c_str();
		}
		Toya::Graphics::Shader* _getShader()
		{
			return Toya::Graphics::ShaderManager::GetActiveShader();
		}
	};
}
