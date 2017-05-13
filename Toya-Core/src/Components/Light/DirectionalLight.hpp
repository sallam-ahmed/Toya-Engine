#pragma once
//#include "PlayerBehaviour.hpp"
#include "Light.hpp"
#include "../../CoreDrivers/Lighting.hpp"

namespace GamePlay
{
	class DirectionalLight : public Light
	{
		float diffuseFactor, specularFactor;
	public:
		float Intensity;
		DirectionalLight()
		{
			Toya::CoreDrivers::Lighting::RegisterLight(this);
			diffuseFactor = 1.0f;
			specularFactor = 1.0f;
			Intensity = 0.5f;
			LightColor = Toya::CoreDrivers::Color(.1f , 1.0f, .2f, 1.0f);
		}
		void Update() override
		{
			auto lightDirectionVector = glm::vec3(transform->Rotation.x, transform->Rotation.y, transform->Rotation.z);
			
			_getShader()->SetUniform3f(_getAttrib("direction").c_str(),lightDirectionVector);
			
			_getShader()->SetUniform4f(_getAttrib("color").c_str(),*LightColor.GetGlm());
			
			_getShader()->SetUniform1f(_getAttrib("dFactor").c_str(), diffuseFactor);
			
			_getShader()->SetUniform1f(_getAttrib("sFactor").c_str(), specularFactor);
		}
	private:
		inline std::string _getAttrib(std::string attribName) const
		{
			std::string qualifier = ("dirLight.");
			return (qualifier + attribName);
		}
	};
}
