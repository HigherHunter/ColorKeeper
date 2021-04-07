#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	~Texture();

	bool LoadTexture(GLint wrapping);
	bool LoadTextureWithAlpha(GLint wrapping);
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};