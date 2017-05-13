#pragma once
#include "../Base/Component.hpp"
#include "../../CoreDrivers/Color.hpp"
#include "../../Graphics/Shader.hpp"

namespace GamePlay
{
	class Light : public Toya::Components::Component
	{

	public:
		Light() = default;
		~Light(){}
		Toya::CoreDrivers::Color LightColor;
	protected:
		Toya::Graphics::Shader* _getShader() { return Toya::Graphics::ShaderManager::GetActiveShader(); }
	};
}
