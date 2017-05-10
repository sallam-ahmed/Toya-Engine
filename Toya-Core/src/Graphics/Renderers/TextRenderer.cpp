#include "TextRenderer.hpp"
#include "../../CoreDrivers/Screen.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H
namespace Toya
{
	namespace Graphics
	{
		GLuint TextRenderer::VAO;
		GLuint TextRenderer::VBO;
		Shader* TextRenderer::TextShader;
		std::map<GLchar, Character> TextRenderer::FontCharacters;
		void TextRenderer::RenderText(float x, float y, std::string text,float scale, glm::vec4 color)
		{
			// Activate corresponding render state	
			TextShader->Enable();
			TextShader->SetUniform4f("textColor", color);
			TextShader->SetUniformMat4("_projectionMatrixS", glm::ortho(0.0f, CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, 0.0f));
			TextShader->SetUniform1i("text", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);
			// Iterate through all characters
			std::string::const_iterator c;
			for (auto i = 0; i < text.size(); i++)
			//for (c = text.begin(); c != text.end(); ++c)
			{
				Character ch = FontCharacters[text[i]];

				GLfloat xpos = x + (ch.Bearing.x * scale );
				GLfloat ypos = y + (FontCharacters['H'].Bearing.y - ch.Bearing.y) * scale;

				GLfloat w = ch.Size.x * scale;
				GLfloat h = ch.Size.y * scale;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 0.0 },
					{ xpos,     ypos,       0.0, 0.0 },

					{ xpos,     ypos + h,   0.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 1.0 },
					{ xpos + w, ypos,       1.0, 0.0 }
				};
				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Now advance cursors for next glyph
				x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
				
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			TextShader->Disable();
		}

		void TextRenderer::LoadFont(std::string fontPath, GLuint fontSize)
		{
			// First clear the previously loaded Characters
			FontCharacters.clear();
			// Then initialize and load the FreeType library
			
			FT_Library ft;
			if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
				fprintf(stderr, "ERROR::FREETYPE: Could not init FreeType Library.\n");
			// Load font as face
			FT_Face face;
			if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
				fprintf(stderr, "ERROR::FREETYPE: Failed to load font.\n");
			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, fontSize);
			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			// Then for the first 128 ASCII characters, pre-load/compile their characters and store them
			for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					fprintf(stderr, "ERROR::FREETYTPE: Failed to load Glyph.\n");
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				FontCharacters.insert(std::pair<GLchar, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			// Destroy FreeType once we're finished
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}

		void TextRenderer::Init()
		{
		
			TextShader = ShaderManager::LoadShader(TEXT_VS_SHADER, TEXT_FRAG_SHADER);
			TextShader->Enable();
			TextShader->SetUniformMat4("_projectionMatrix", glm::ortho(0.0f,CoreDrivers::Screen::ScreenWidth, CoreDrivers::Screen::ScreenHeight, 0.0f));
			TextShader->SetUniform1i("text", 0);
		
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
}
