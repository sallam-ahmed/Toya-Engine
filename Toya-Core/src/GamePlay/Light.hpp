#pragma once

namespace GamePlay
{
	class Light : public Toya::Components::Behaviour
	{
	public:
		Light() = default;
		~Light(){}
		Toya::CoreDrivers::Color LightColor;
		virtual void UpdateLoop() = 0;
	};
}
