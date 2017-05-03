#pragma once
#include <GLM/glm.hpp>
#include "../Components/Model.hpp"

namespace Toya
{
	namespace Math
	{
		struct AABB
		{
			
			glm::vec3 min;
			glm::vec3 max;
			float minX;
			float minY;
			float minZ;

			float maxX, maxY, maxZ;
		public:
			AABB(Components::Model& model)
			{
				_constructAABB(model);
			}
			
		private:
			void _constructAABB(Components::Model& model)
			{
				for(auto m : model.meshes)
				{
					for(auto v : m.vertices)
					{
						if (minX > v.vPosition.x)
							minX = v.vPosition.x;
						if (minY > v.vPosition.y)
							minY = v.vPosition.y;
						if (minZ > v.vPosition.z)
							minZ = v.vPosition.z;

						if (maxX < v.vPosition.x)
							maxX = v.vPosition.x;
						if (maxY < v.vPosition.y)
							maxY = v.vPosition.y;
						if (maxZ < v.vPosition.z)
							maxZ = v.vPosition.z;
					}
				}

				//min and max found

			}
		};
	}
}
