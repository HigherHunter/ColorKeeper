#include "Shapes.h"

Mesh* Shapes::SquareShapeMeshRepeatTexture(const btVector3& halfSize, const btVector3& objectColor)
{
	const float halfWidth = halfSize.x();
	const float halfHeight = halfSize.y();
	const float halfDepth = halfSize.z();

	static unsigned int squareIndices[] = {
		0, 2, 1,
		1, 2, 3,
	};

	GLfloat squareVertices[] = {
		// X, Y, Z								R, G, B,														U, V					normX, normY, normZ
	   -halfWidth, halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 0.0f,				0.0f, -1.0f, 0.0f,// bot left
		halfWidth, halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		halfWidth, 0.0f,		0.0f, -1.0f, 0.0f,// back
	   -halfWidth, halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, halfDepth,		0.0f, -1.0f, 0.0f,// bot right
		halfWidth, halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		halfWidth, halfDepth,	0.0f, -1.0f, 0.0f// top
	};

	Mesh* customSquare = new Mesh();
	customSquare->CreateMesh(squareVertices, squareIndices, 44, 6);
	return customSquare;
}

class Mesh* Shapes::SquareShapeMeshStretchTexture(const btVector3& halfSize, const btVector3& objectColor)
{
	const float halfWidth = halfSize.x();
	const float halfHeight = halfSize.y();
	const float halfDepth = halfSize.z();

	static unsigned int squareIndices[] = {
		0, 2, 1,
		1, 2, 3,
	};

	GLfloat squareVertices[] = {
		// X, Y, Z								R, G, B,														U, V			normX, normY, normZ
	   -halfWidth, halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,// bot left
		halfWidth, halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,// back
	   -halfWidth, halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,// bot right
		halfWidth, halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 1.0f,		0.0f, -1.0f, 0.0f// top
	};

	Mesh* customSquare = new Mesh();
	customSquare->CreateMesh(squareVertices, squareIndices, 44, 6);
	return customSquare;
}

Mesh* Shapes::CubeShapeMesh(const btVector3& halfSize, const btVector3& objectColor)
{
	const float halfWidth = halfSize.x();
	const float halfHeight = halfSize.y();
	const float halfDepth = halfSize.z();

	static unsigned int cubeIndices[] = {
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
		// X, Y, Z									R, G, B,														U, V			normX, normY, normZ
		-halfWidth, -halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Face bottom left 0
		 halfWidth, -halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Face bottom right 1
		 halfWidth,  halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Face top right 2
		-halfWidth,  halfHeight, -halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Face top left 3
		 halfWidth, -halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Back bottom right 4
		-halfWidth, -halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// Back bottom left 5
		-halfWidth,  halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// Back top left 6
		 halfWidth,  halfHeight,  halfDepth,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 0.0f,		0.0f, 0.0f, 0.0f	// Back top right 7
	};

	CalcAverageNormals(cubeIndices, 36, cubeVertices, 88, 11, 8, true);

	Mesh* customCube = new Mesh();
	customCube->CreateMesh(cubeVertices, cubeIndices, 88, 36);
	return customCube;
}

Mesh* Shapes::PyramidShapeMesh(const btVector3& objectColor)
{
	static unsigned int pyramidIndices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0, // front
		0, 1, 2
	};

	GLfloat pyramidVertices[] = {
		// X, Y, Z				R, G, B,														U, V			normX, normY, normZ
	   -1.0f, -1.0f, -0.6f,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bot left
		0.0f, -1.0f, 1.0f,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,	// back
		1.0f, -1.0f, -0.6f,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bot right
		0.0f, 1.0f, 0.0f,		objectColor.getX(), objectColor.getY(), objectColor.getZ(),		0.5f, 1.0f,		0.0f, 0.0f, 0.0f	// top
	};

	CalcAverageNormals(pyramidIndices, 12, pyramidVertices, 44, 11, 8, true);

	Mesh* customPyramid = new Mesh();
	customPyramid->CreateMesh(pyramidVertices, pyramidIndices, 44, 12);
	return customPyramid;
}

void Shapes::CalcAverageNormals(unsigned* indices, unsigned indicesCount, GLfloat* vertices, unsigned verticesCount, unsigned verticesLength, unsigned normalOffset, bool switched)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * verticesLength;
		unsigned int in1 = indices[i + 1] * verticesLength;
		unsigned int in2 = indices[i + 2] * verticesLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;

	}

	for (size_t i = 0; i < verticesCount / verticesLength; i++)
	{
		unsigned int normOffset = i * verticesLength + normalOffset;
		glm::vec3 vec(vertices[normOffset], vertices[normOffset + 1], vertices[normOffset + 2]);
		vec = glm::normalize(vec);
		vertices[normOffset] = vec.x; vertices[normOffset + 1] = vec.y; vertices[normOffset + 2] = vec.z;
	}
}