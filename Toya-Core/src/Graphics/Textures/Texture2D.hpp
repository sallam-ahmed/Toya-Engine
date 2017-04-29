#pragma once
#include <GLEW/GL/glew.h>
#include <string>
#include <assimp/types.h>

#define TEXTURE_DIFFUSE "texture_diffuse"
#define TEXTURE_SPECULAR "texture_specular"
namespace Toya
{
	namespace Graphics
	{
		struct Texture2D
		{
			friend class TextureLoader;
		public:
			aiString path;
			std::string type;
			GLboolean MipMaps;
			int TextureUnit;
			/*Ranges from 0 to 16 */

			void Bind() const
			{
				glActiveTexture(_getTextureUnitGPU());
			}
			void Unbind() const
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			~Texture2D()
			{
				glDeleteTextures(1, &m_TextureId);
			}
		private:
			GLuint m_TextureId = NULL;
			inline GLint _getTextureUnitGPU() const
			{
				return TextureUnit + GL_TEXTURE0;
			}
		};
	}
}