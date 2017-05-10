#pragma once
#include "GLM/glm.hpp"
#include "../Components/Base/Transform.hpp"
#include "../Components/Model.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"

namespace Toya
{
	namespace Math
	{
		class AxisAlignedBoundingBox
		{
			float m_MinX = 99999.99999f , m_MinY = 99999.99f, m_MinZ = 99999.999f;
			float m_MaxX = -999999.0f , m_MaxY = -999999.0f , m_MaxZ = -999999.09f;
			glm::vec3 m_MinVertexPosition;
			glm::vec3 m_MaxVertexPosition;
			glm::vec3 m_BoxSize;
			
			glm::vec3 m_CenterPoint;
			glm::vec3 m_HalfSize;
		public:
			Components::Model* bindingModel;

			AxisAlignedBoundingBox() = default;
			AxisAlignedBoundingBox(Components::Transform* model)
			{
			
				bindingModel = model->GetComponent<Components::Model>();

				for(auto mesh : bindingModel->meshes)
				{
					for(auto vert : mesh.vertices)
					{
						if (m_MinX > vert.vPosition.x)
							m_MinX = vert.vPosition.x;

						if (m_MinY > vert.vPosition.y)
							m_MinY = vert.vPosition.y;

						if (m_MinZ > vert.vPosition.z)
							m_MinZ = vert.vPosition.z;

						if (m_MaxX < vert.vPosition.x)
							m_MaxX = vert.vPosition.x;

						if (m_MaxY < vert.vPosition.y)
							m_MaxY = vert.vPosition.y;

						if (m_MaxZ < vert.vPosition.z)
							m_MaxZ = vert.vPosition.z;
					}
				}

				m_MinVertexPosition = glm::vec3(m_MinX, m_MinY, m_MinZ);
				m_MaxVertexPosition = glm::vec3(m_MaxX, m_MaxY, m_MaxZ);
				
				m_CenterPoint = glm::vec3((m_MinX + m_MaxX) / 2.0f, (m_MinY + m_MaxY) / 2.0f, (m_MinZ + m_MaxZ) / 2.0f);
				m_BoxSize = glm::vec3(glm::abs(m_MaxX - m_MinX), glm::abs(m_MaxY - m_MinY), glm::abs(m_MaxZ -  m_MinZ));
				m_HalfSize = glm::vec3(m_BoxSize.x / 2, m_BoxSize.y / 2, m_BoxSize.z / 2);
			}

			inline glm::vec3 GetCenterPoint() const { return m_CenterPoint; }
			inline glm::vec3 GetHalfSize()const  { return m_HalfSize; }
			
			inline bool IsIntersecting(AxisAlignedBoundingBox* other) const
			{
				auto diff = glm::abs(m_CenterPoint - other->GetCenterPoint());
				auto sizeAdd = m_HalfSize + other->GetHalfSize();
				return (diff.x <= sizeAdd.x && diff.y <= sizeAdd.y && diff.z <= sizeAdd.z);
			}

			inline void TransformAABB(glm::mat4& tMatrix)
			{
				auto minVert = glm::vec4(m_MinVertexPosition, 1.0f);
				auto maxVert = glm::vec4(m_MaxVertexPosition, 1.0f);

				minVert = tMatrix * minVert;
				maxVert = tMatrix * maxVert;

				m_CenterPoint = glm::vec3(minVert + maxVert);
				m_CenterPoint /= 2;

				m_BoxSize = glm::vec3(glm::abs(maxVert - minVert));

				m_HalfSize = m_BoxSize;
				m_HalfSize /= 2;
			}
		};

		typedef AxisAlignedBoundingBox AABB;
	}
}
