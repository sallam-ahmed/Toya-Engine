#pragma once
#include "../../CoreDrivers/Color.hpp"
#include "Light.hpp"

using namespace Toya::CoreDrivers;
namespace Toya
{
	namespace Graphics
	{

		class DirectionalLight : Light
		{
		public:
			Color LightColor = Color(1, 0, 0, 1);
			float LightIntensity;
			DirectionalLight()
			{
				LightColor = Color(1,0,0,1);
				LightIntensity = 1.0f;
			}
			~DirectionalLight() override
			{
				
			}
		};
	}
}
