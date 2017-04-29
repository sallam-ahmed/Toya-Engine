#pragma once
#include "../Components/Mesh.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
using namespace Assimp;
namespace Toya
{
	namespace CoreDrivers
	{
		class AssetManager
		{
			static Importer m_AssetImporter;
			 const aiScene *m_AssetScene;

		public:
			AssetManager() = default;
			static Components::Mesh* LoadMesh(std::string filePath,unsigned loadFlags)
			{

			}
		};
		Importer AssetManager::m_AssetImporter;
		//aiScene *AssetManager::m_AssetScene;
	}
}
