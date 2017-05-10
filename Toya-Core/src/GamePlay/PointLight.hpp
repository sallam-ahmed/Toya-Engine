#pragma once
#include "../CoreDrivers/Lighting.hpp"
namespace GamePlay
{
	class PointLight : public Light
	{
		Toya::Graphics::Shader* m_Shader;
		
		float constF, quadF, linearF,dFactor,sFactor;
	public:
		//Toya::CoreDrivers::Color LightColor;
		int lightIndex = 0;
		PointLight()
		{
			Lighting::RegisterLight(this);
			LightColor = Color::Red;
			
		}
		
		void UpdateLoop() override
		{
			

			_getShader()->SetUniform3f(_getAttrib("position"), transform->Position);
			_getShader()->SetUniform4f(_getAttrib("color"), *(LightColor.GetGlm()));
			_getShader()->SetUniform1f(_getAttrib("dFactor"), dFactor);
			_getShader()->SetUniform1f(_getAttrib("sFactor"), sFactor);
			_getShader()->SetUniform1f(_getAttrib("constant"), constF);
			_getShader()->SetUniform1f(_getAttrib("linear"), linearF);
			_getShader()->SetUniform1f(_getAttrib("quadratic"), quadF);
			
		}
	private:
		inline const GLchar* _getAttrib(std::string attribName) const
		{
			std::string qualifier = ("pointLights[" + std::to_string(lightIndex) + "].");
			return (qualifier + attribName).c_str();
		}
		inline Toya::Graphics::Shader* _getShader() { return Toya::Graphics::ShaderManager::GetActiveShader(); }
	public:
		void Start() override
		{
			constF = 1.0f;
			quadF = .032f;
			linearF = .09f;
			dFactor = 1.0f;
			sFactor = .7f;
			lightIndex = Lighting::GetNextLightIndex();
		}

		void Update() override
		{
		}

		void OnEnable() override
		{
		}
	};
}
