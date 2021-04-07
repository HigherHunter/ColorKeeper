#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderText.h"
#include "ft2build.h"
#include FT_FREETYPE_H

class TextManager
{
public:
	TextManager();

	void LoadTextCharacters();
	
	void RenderText(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	bool RenderText(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 normalColor, glm::vec3 selectedColor, glm::vec2 mousePos);
	
	void RenderTextMiddle(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	bool RenderTextMiddle(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 normalColor, glm::vec3 selectedColor, glm::vec2 mousePos);
	
	void RenderTextEnd(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	bool RenderTextEnd(ShaderText& shaderText, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 normalColor, glm::vec3 selectedColor, glm::vec2 mousePos);
	
private:
	// Information relevant to a character as FreeType
	struct Character {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance; // Horizontal offset to advance to next glyph
	};
	
	std::map<GLchar, Character> Characters;

	GLuint VAO, VBO;
};