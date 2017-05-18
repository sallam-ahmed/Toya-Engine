#include "TextureLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <xhash>

namespace Toya
{
	namespace Graphics
	{
		GLboolean* TextureLoader::loadedTextures = new GLboolean[16]{false};
		std::map<int, Texture2D*> TextureLoader::m_TextureBank;
		Texture2D* TextureLoader::LoadTexture(std::string texturePath, int textureUnit, GLboolean generateMIP, std::string tex_type)
		{
			auto hashValue = Utils::_hash(texturePath.c_str());
			if (IsLoaded(texturePath))
				return m_TextureBank[hashValue];

			Texture2D* _texture = new Texture2D();
			_texture->TextureUnit = textureUnit;
			int width, height, numComponents;
			unsigned char* data = stbi_load((texturePath).c_str(), &width, &height, &numComponents, TEXTURE_CHANNEL_NUMBER);
			if (data == NULL)
			{
				fprintf(stderr, "Unable to load texture: %s\n", texturePath.c_str());
				return nullptr;
			}

			glBindTexture(GL_TEXTURE_2D, 0);
			glGenTextures(1, &_texture->m_TextureId);
			glBindTexture(GL_TEXTURE_2D, _texture->m_TextureId);
			auto bIsTexture = glIsTexture(_texture->m_TextureId);
			fprintf(stdout, "Texture %s Load Status : %s\n", texturePath.c_str(), bIsTexture == 1 ? "Suc" : "Fail");
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (generateMIP)
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
			_texture->type = tex_type;
			//system("pause");
			m_TextureBank[hashValue] = _texture;
			return _texture;
		}
		void TextureLoader::LoadCubeMapTexture(CubeMap* cubeMap)
		{
			int width, height, numComponents;

			glGenTextures(1, &cubeMap->TextureId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->TextureId);
			for (int i = 0; i < cubeMap->texture_faces.size(); ++i)
			{
				fprintf(stdout, "Loaded %i\n", i);
				auto data = stbi_load((cubeMap->texture_faces[i].c_str()), &width, &height, &numComponents, 3);
				if (data == NULL)
					fprintf(stderr, "Error while loading texture %i at path %s\n", i, cubeMap->texture_faces[i].c_str());
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}
