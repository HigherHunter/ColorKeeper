#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class ShaderText
{
public:
	ShaderText();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	void UseShader();
	void ClearShader();

	GLuint GetShaderProgram() const { return shaderID; }

	~ShaderText();
	
private:
	GLuint shaderID;
	
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};