#pragma once
#include "Texture2D.hpp"
#include <string>

#include <vector>
#include <map>
#include "../../Utils/FileUtils.hpp"

namespace Toya
{
	namespace Graphics
	{
		struct CubeMap
		{
			std::vector<std::string> texture_faces;
			GLuint TextureId;
		};
#define TEXTURE_CHANNEL_NUMBER 4
		class TextureLoader
		{
			
			static std::map<int, Texture2D*> m_TextureBank;

		public:
			/**
			    * \brief Load a texture2d from a file path
			    * \param texturePath File path to image file
			    * \param textureUnit The target unit index for texure, leave to allocate automaticly
			    * \param generateMIP Generate MIP Map, will generate by default
			    * \return Pointer to Texture2D
			    */
			static Texture2D* LoadTexture(std::string texturePath, int textureUnit = 0, GLboolean generateMIP = true, std::string tex_type = TEXTURE_DIFFUSE);
			static void	LoadCubeMapTexture(CubeMap* cubeMap);
			inline static bool IsLoaded(std::string texturePath)
			{
				return (m_TextureBank[Utils::_hash(texturePath.c_str())] != nullptr);
			}

			static GLboolean *loadedTextures;
		};
		
	}
}
