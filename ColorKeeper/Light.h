#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShadowMap.h"

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambIntensity, GLfloat diffIntensity,
		GLfloat shadowWidth, GLfloat shadowHeight);

	ShadowMap* GetShadowMap() { return shadowMap; }

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	glm::mat4 lightProj;

	ShadowMap* shadowMap;
};