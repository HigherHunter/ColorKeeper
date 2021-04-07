#include "DebugDrawer.h"

#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	float fromX = from.getX(), fromY = from.getY(), fromZ = from.getZ();
	float toX = to.getX(), toY = to.getY(), toZ = to.getZ();
	float lineSize = 0.05;

	unsigned int cubeIndices[] = {
	0, 1, 3,
	3, 1, 2,
	1, 4, 2,
	2, 4, 7,
	4, 5, 7,
	7, 5, 6,
	5, 0, 6,
	6, 0, 3,
	3, 2, 6,
	6, 2, 7,
	5, 4, 0,
	0, 4, 1
	};

	GLfloat cubeVertices[] = {
		// X, Y, Z												R, G, B,				U, V			normX, normY, normZ
		fromX - lineSize, fromY - lineSize, fromZ - lineSize,	0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Face bottom left
		fromX + lineSize, fromY - lineSize, fromZ - lineSize,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Face bottom right
		fromX + lineSize, fromY + lineSize, fromZ - lineSize,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Face top right
		fromX - lineSize, fromY + lineSize, fromZ - lineSize,	0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Face top left

		toX + lineSize, toY - lineSize,  toZ + lineSize,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Back bottom right 
		toX - lineSize, toY - lineSize,  toZ + lineSize,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Back bottom left
		toX - lineSize, toY + lineSize,  toZ + lineSize,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Back top left
		toX + lineSize, toY + lineSize,  toZ + lineSize,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f	// Back top right
	};

	Mesh* mojCube = new Mesh();
	mojCube->CreateMesh(cubeVertices, cubeIndices, 88, 36);

	// MOJ CUBE
	glm::mat4 model = glm::mat4();
	glUniformMatrix4fv(passedUniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mojCube->RenderMesh();
	mojCube->ClearMesh();
}

void DebugDrawer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	// draws a line between two contact points
	btVector3 const startPoint = pointOnB;
	btVector3 const endPoint = pointOnB + normalOnB * distance;
	drawLine(startPoint, endPoint, color);
}

void DebugDrawer::ToggleDebugFlag(int flag)
{
	if (debugMode & flag)
		// flag is enabled, so disable it
		debugMode = debugMode & (~flag);
	else
		// flag is disabled, so enable it
		debugMode |= flag;
}