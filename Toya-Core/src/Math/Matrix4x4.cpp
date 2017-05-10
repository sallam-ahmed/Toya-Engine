#include "Matrix4x4.hpp"
#include <cstdio>

namespace Toya
{
	namespace Math
	{
		Matrix4x4 Matrix4x4::Identity = Matrix4x4(1.0f);

		Matrix4x4::Matrix4x4()
		{
			m_data = new GLfloat[16]{
				1.0f,	0.0f,	0.0f,	0.0f,
				0.0f,	1.0f,	0.0f,	0.0f,
				0.0f,	0.0f,	1.0f,	0.0f,
				0.0f,	0.0f,	0.0f,	1.0f
			};
			auto d = 1.0f;
			m_glmMatrix = new glm::mat4(d);
			/*	X0 = d;			Y0 = 0;			Z0 = 0;			W0 = 0;
			X1 = 0;			Y1 = d;			Z1 = 0;			W1 = 0;
			X2 = 0;			Y2 = 0;			Z2 = d;			W2 = 0;
			X3 = 0;			Y3 = 0;			Z3 = 0;			W3 = d;*/


		}

		Matrix4x4::Matrix4x4(float d)
		{
			m_glmMatrix = new glm::mat4(d);

			/*X0 = d;			Y0 = 0;			Z0 = 0;			W0 = 0;
			X1 = 0;			Y1 = d;			Z1 = 0;			W1 = 0;
			X2 = 0;			Y2 = 0;			Z2 = d;			W2 = 0;
			X3 = 0;			Y3 = 0;			Z3 = 0;			W3 = d;*/

			m_data = new GLfloat[16]{
				d,	0.0f,	0.0f,	0.0f,
				0.0f,	d,	0.0f,	0.0f,
				0.0f,	0.0f,	d,	0.0f,
				0.0f,	0.0f,	0.0f,	d
			};

		}

		Matrix4x4::Matrix4x4(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3)
		{
			m_glmMatrix = new glm::mat4(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3);

			/*	X0 = x0;		Y0 = y0;		Z0 = z0;		W0 = w0;
			X1 = x1;		Y1 = y1;		Z1 = z1;		W1 = w1;
			X2 = x2;		Y2 = y2;		Z2 = z2;		W2 = w2;
			X3 = x3;		Y3 = y3;		Z3 = z3;		W3 = w3;*/

			m_data = new GLfloat[16]{
				x0,y0,z0,w0,
				x1,y1,z1,w1,
				x2,y2,z2,w2,
				x3,y3,z3,w3,
			};
		}

		Matrix4x4::~Matrix4x4()
		{
			/*delete m_glmMatrix;
			delete m_data;*/
		}
		glm::mat4* Matrix4x4::GetGlm() const
		{
			return m_glmMatrix;
		}
		GLfloat* Matrix4x4::GetElements() const
		{
			return m_data;
		}

		Matrix4x4::Matrix4x4(glm::mat4 mat)
		{
			if (m_glmMatrix != nullptr)
				delete m_glmMatrix;

			m_glmMatrix = new glm::mat4(mat);
			m_data = new GLfloat[16]{ 0.0f };
			const float *pSource = (const float*)(glm::value_ptr(mat));
			for (int i = 0; i < 16; ++i)
			{
				m_data[i] = pSource[i];
			}
		}
	}
}
