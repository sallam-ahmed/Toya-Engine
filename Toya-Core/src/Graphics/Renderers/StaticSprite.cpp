#include "StaticSprite.hpp"


namespace Toya
{
	namespace Graphics
	{
		namespace Renderers
		{

			StaticSprite::StaticSprite(float x, float y, float width, float height, glm::vec4 color, Shader& shader) :
				Renderable2D(glm::vec3(x, y, 0), glm::vec2(width,height),color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();
				GLfloat vertices[] = {
					0,		0,		0,
					0,		height,	0,
					width,	height,	0,
					width,	0,		0
				};
				GLfloat colors[] = {
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
				};
				m_VertexArray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->AddBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] = { 0,1,2,2,3,0 }; // A Simple Double Triangled Square
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}
			StaticSprite::StaticSprite(const glm::vec3 &pos,const glm::vec2& size, glm::vec4 color, Shader& shader) :
				Renderable2D(pos,size, color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();
				GLfloat vertices[] = {
					0,		0,		0,
					0,		size.y,	0,
					size.x,	size.y,	0,
					size.x,	0,		0
				};
				GLfloat colors[] = {
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
				};
				m_VertexArray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->AddBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] = { 0,1,2,2,3,0 }; // A Simple Double Triangled Square
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}


			StaticSprite::~StaticSprite()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}
		}
	}
}