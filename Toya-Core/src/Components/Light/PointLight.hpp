#pragma once
#include "../../CoreDrivers/Lighting.hpp"
namespace GamePlay
{
	using namespace Toya::CoreDrivers;
	class PointLight : public Light
	{
		float constF, quadF, linearF,dFactor,sFactor;
	public:
		int lightIndex = 0;
		PointLight()
		{
			Toya::CoreDrivers::Lighting::RegisterLight(this);
			LightColor = Toya::CoreDrivers::Color::Red;

			constF = 1.0f;
			quadF = .032f;
			linearF = .09f;
			dFactor = 1.0f;
			sFactor = .7f;
			lightIndex = Lighting::GetNextLightIndex();
		}
		
		void Update() override
		{
			_getShader()->SetUniform3f(_getAttrib("position").c_str(), transform->Position);
			_getShader()->SetUniform4f(_getAttrib("color").c_str(), *(LightColor.GetGlm()));
			_getShader()->SetUniform1f(_getAttrib("dFactor").c_str(), dFactor);
			_getShader()->SetUniform1f(_getAttrib("sFactor").c_str(), sFactor);
			_getShader()->SetUniform1f(_getAttrib("constant").c_str(), constF);
			_getShader()->SetUniform1f(_getAttrib("linear").c_str(), linearF);
			_getShader()->SetUniform1f(_getAttrib("quadratic").c_str(), quadF);
		}
	private:
		inline const std::string _getAttrib(std::string attribName) const
		{
			std::string qualifier = ("pointLights[" + std::to_string(lightIndex) + "].");
			return (qualifier + attribName);
		}
	};
}
