#pragma once
#include <string>
#include <GLEW/GL/glew.h>
#include "../Graphics/Shader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.hpp"
#include "../Graphics/Textures/TextureLoader.hpp"

namespace Toya
{
	namespace Components
	{
		class Model
		{
		public:
			Shader* modelShader;
			Model() = default;
			Model(GLchar* filePath)
			{
				this->_loadModel(filePath);
			}

			void Render()
			{
				Render(modelShader);
			}
			void Render(Graphics::Shader* shader)
			{
				shader->Enable();
				for (auto mesh : meshes)
					mesh.Draw(shader);
			}
		private:
			std::vector<Texture2D> textures_loaded;
			std::vector<Mesh> meshes;
			std::string directory;
			
			void _loadModel(std::string path)
			{
				Assimp::Importer import;
				auto scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
				if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
				{
					fprintf(stderr, "ERROR::ASSIMP:: %s\n", import.GetErrorString());
					return;
				}
				this->directory = path.substr(0, path.find_last_of('/'));
				this->_processNode(scene->mRootNode, scene);
			}
			void _processNode(aiNode* node, const aiScene* scene)
			{
				//Process Node Meshes
				for (GLuint i = 0; i < node->mNumMeshes; i++)
				{
					auto mesh = scene->mMeshes[node->mMeshes[i]];
					this->meshes.push_back(this->_processMesh(mesh, scene));
				}
				//Process children too
				for (GLuint i = 0; i < node->mNumChildren; i++)
				{
					this->_processNode(node->mChildren[i], scene);
				}

				//TODO Preserve Mesh Heirarchy for complex meshes representtation 
			}

			Mesh _processMesh(aiMesh* mesh, const aiScene* scene) 
			{
				std::vector<ComplexVertex> vertices;
				std::vector<GLuint> indices;
				std::vector<Texture2D> textures;

				for (GLuint i = 0; i < mesh->mNumVertices; i++)
				{
					ComplexVertex vertex;
					//Position
					glm::vec3 vect3;
					vect3.x = mesh->mVertices[i].x;
					vect3.y = mesh->mVertices[i].y;
					vect3.z = mesh->mVertices[i].z;
					vertex.vPosition = vect3;
					vertices.push_back(vertex);
					//Normals
					vect3.x = mesh->mNormals[i].x;
					vect3.y = mesh->mNormals[i].y;
					vect3.z = mesh->mNormals[i].z;
					vertex.vNormals = vect3;
					//Tex Coords
					if (mesh->mTextureCoords[0]) //Check for tex Coords
					{
						glm::vec2 vec;
						vec.x = mesh->mTextureCoords[0][i].x;
						vec.y = mesh->mTextureCoords[0][i].y;
						vertex.vTexCoords = vec;
					}
					else
						vertex.vTexCoords = glm::vec2(0.0f, 0.0f);
				}
				// Process indices
				for (GLuint i = 0; i < mesh->mNumFaces; i++)
				{
					auto face = mesh->mFaces[i];
					for (GLuint j = 0; j < face.mNumIndices; j++)
						indices.push_back(face.mIndices[j]);
				}
				// Process material
				if (mesh->mMaterialIndex >= 0)
				{
					aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
					std::vector<Texture2D> diffuseMaps = this->_loadMaterialTextures(material,
						aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);

					textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

					std::vector<Texture2D> specularMaps = this->_loadMaterialTextures(material,
						aiTextureType_SPECULAR, TEXTURE_SPECULAR);

					textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
				}
				return Mesh(vertices, textures,indices);
			}

			std::vector<Texture2D> _loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) 
			{
				std::vector<Texture2D> textures;
				for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
				{
					aiString str;
					mat->GetTexture(type, i, &str);
					auto skipTex = false;
					for( auto loadedTex : textures_loaded)
					{
						if(std::strcmp(loadedTex.path.C_Str(),str.C_Str()) == 0)
						{
							textures.push_back(loadedTex);
							skipTex = true;
							break;
						}
					}
					if (!skipTex) {
						auto texPath = directory + "/" + str.C_Str();
						auto texture = TextureLoader::LoadTexture(texPath, i, true, typeName);
						texture->path = str;
						textures.push_back(*texture);
						this->textures_loaded.push_back(*texture);
					}
				}
				return textures;
			}
		};
	}
}
