#pragma once
#include "../Math/Math.hpp"
#include "../Graphics/Buffers/VertexArray.hpp"
#include "../Graphics/Buffers/Buffers.h"
#include "../Graphics/Renderers/Base/VertexData.hpp"
#include "../Graphics/Textures/Texture2D.hpp"
#include "Base/RenderableComponent.hpp"
#include <sstream>


#define EXP 0
#define BUFFER_OFFSET(i) (GLvoid*)(i)
namespace Toya
{
using namespace Graphics;
	namespace Components
	{
		class Mesh : public Component
		{
#if EXP
			VertexArray *m_VAO;
			IndexBuffer *m_IBO;
#endif
		public:
			std::vector<ComplexVertex> vertices;
			std::vector<Texture2D> textures;
			std::vector<GLuint> indices;
			std::vector<GLfloat> uvMapping;

			Mesh(std::vector<ComplexVertex> verts,std::vector<Texture2D> tex, std::vector<GLuint> indcs)
			{
				this->vertices = verts;
				this->textures = tex;
				this->indices = indcs;
				this->_setupMesh();
			}
#if EXP
			VertexArray *GetVAO()const
			{
				return m_VAO;
			}
			IndexBuffer *GetIBO() const
			{
				return m_IBO;
			}
#endif
			void Draw(Shader *shader)
			{
#if 1
				// Bind
				GLuint diffuseNr = 1;
				GLuint specularNr = 1;
				glEnable(GL_TEXTURE_2D);
				for (GLuint i = 0; i < this->textures.size(); i++)
				{
					glActiveTexture(GL_TEXTURE0 + i); 
					std::stringstream ss;
					std::string number;
					std::string name = this->textures[i].type;
					if (name == "texture_diffuse")
						ss << diffuseNr++; 
					else if (name == "texture_specular")
						ss << specularNr++;
					number = ss.str();
					shader->SetUniform1i((name + number).c_str(), i);
			//		fprintf(stdout, "Activating texture of %u\n",textures[i].m_TextureId);
					glBindTexture(GL_TEXTURE_2D, this->textures[i].m_TextureId);
				}

				//shader->SetUniform1f("material.shininess", 16.0f);

				glBindVertexArray(this->VAO);
				glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);

				// Always good practice to set everything back to defaults once configured.
				for (GLuint i = 0; i < this->textures.size(); i++)
				{
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
#endif
			}

			void DrawOneTexture(Shader * shader,Texture2D *tex)
			{
				shader->SetUniform1i("material.diffuse",0);
				//TODO Add Specular Map
				shader->SetUniform1f("material.shininess", 13.0f);
				tex->Bind();
				
				//shader->SetUniform1f("material.shininess", 16.0f);
				
				glBindVertexArray(this->VAO);
				glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		private:
			GLuint VAO, VBO, EBO;
			void _setupMesh()
			{
				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);
				glGenBuffers(1, &this->EBO);
				glBindVertexArray(this->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(ComplexVertex),
					&this->vertices[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
					&this->indices[0], GL_STATIC_DRAW);
				// Vertex Positions
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ComplexVertex),
					BUFFER_OFFSET(0));
				// Vertex Normals
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ComplexVertex),
					BUFFER_OFFSET(offsetof(ComplexVertex, vNormals)));
				// Vertex Texture Coords
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ComplexVertex),
					BUFFER_OFFSET(offsetof(ComplexVertex, vTexCoords)));
				glBindVertexArray(0);
			}
#if EXP
			void _setupMesh_comples()
			{
				m_VAO = new VertexArray();
				m_VAO->Bind();
				/*				*SUGGESTED VERTEX BUFFERING FORMAT*
				 ************************ ONE BUFFER ********************************
				 *	 POSITION		 NORMALS			COLOR		TEXTURE_MAPPING *
				 *	X	Y	Z		X	Y	Z		R	G	B	A		U	V	    *
				 ********************************************************************
				 */
				 //Vertex Buffer Object
				auto vBufSize = vertices.size() * 3;
				GLfloat *meshVertexBuffer = new GLfloat[vBufSize]{0};
				auto j = 0;
				for(auto i = 0 ; i < vBufSize; i += 3)
				{
					meshVertexBuffer[i] = vertices[j].vPosition.x; //X
					meshVertexBuffer[i + 1] = vertices[j].vPosition.y;; //Y
					meshVertexBuffer[i + 2] = vertices[j].vPosition.z;; //Z
					++j;
				}
				m_VAO->AddBuffer(new Buffer(meshVertexBuffer, vBufSize, 3), 0);
				j = 0;
				GLfloat *normalsVertexBuffer = new GLfloat[vBufSize];
				for (auto i = 0; i < vBufSize; i += 3)
				{
					normalsVertexBuffer[i] = vertices[j].vNormals.x; //X
					normalsVertexBuffer[i + 1] = vertices[j].vNormals.y; //Y
					normalsVertexBuffer[i + 2] = vertices[j].vNormals.z; //Z
					j++;
				}
				m_VAO->AddBuffer(new Buffer(normalsVertexBuffer, vBufSize, 3), 1);
				j = 0;
				auto tBufSize = vertices.size() * 2;
				GLfloat *texBufferObject = new GLfloat[tBufSize];
				for (auto i = 0; i < tBufSize; i += 2)
				{
					texBufferObject[i] = vertices[j].vTexCoords.x; //X
					texBufferObject[i + 1] = vertices[j].vTexCoords.y; //Y
					j++;
				}
				m_VAO->AddBuffer(new Buffer(texBufferObject, tBufSize, 2), 2);
				j = 0;
				//Index Buffer Object
				m_IBO = new IndexBuffer();
				//for (auto i = 0; i < bufSize; i += 8)
				//{
				//	meshVertexBuffer[i] = 0; //Nx
				//	meshVertexBuffer[i + 1] = 0;//Ny
				//	meshVertexBuffer[i + 2] = 0;//Nz
				//	
				//	
				//}
				//for (auto i = 0; i < bufSize; i += 8)
				//{
				//	meshVertexBuffer[i] = 0; //Nx
				//	meshVertexBuffer[i + 1] = 0;//Ny
				//}
			
				
			//	m_VAO->AddBuffer(new Buffer(meshVertexBuffer, bufSize, 8), 0);
				//m_VAO->AddBuffer(new Buffer(meshNormalsBuffer, normalBufSize, 3), 1);
				//m_VAO->AddBuffer(new Buffer(meshUvBuffer, uvBufSize, 2), 2);

				
			}
#endif
		};
	}
}
