#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"

#include "Mesh.h"

class Shapes
{
public:
	enum ShapeTypes { squareRepeat, squareStretch, cube, pyramid };

	static Mesh* SquareShapeMeshRepeatTexture(const btVector3& halfSize, const btVector3& objectColor);
	static Mesh* SquareShapeMeshStretchTexture(const btVector3& halfSize, const btVector3& objectColor);
	static Mesh* CubeShapeMesh(const btVector3& halfSize, const btVector3& objectColor);
	static Mesh* PyramidShapeMesh(const btVector3& objectColor);

	static void CalcAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset, bool switched);
};