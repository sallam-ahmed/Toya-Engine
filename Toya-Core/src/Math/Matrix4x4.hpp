#pragma once
#include <GLM/mat4x4.hpp>
#include <GLEW/GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>

namespace Toya
{
	namespace Math
	{
		class Matrix4x4
		{
			glm::mat4* m_glmMatrix;
			GLfloat* m_data;
		public:
			static Matrix4x4 Identity;
			/*float
			X0, Y0, Z0, W0,
			X1, Y1, Z1, W1,
			X2, Y2, Z2, W2,
			X3, Y3, Z3, W3;*/
			Matrix4x4();
			Matrix4x4(float d);
			Matrix4x4(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3);
			explicit Matrix4x4(glm::mat4 mat);
			~Matrix4x4();
			glm::mat4* GetGlm() const;
			GLfloat* GetElements() const;


		};
	}
}