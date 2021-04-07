#include "GameObject.h"

GameObject::GameObject(btCollisionShape* shape, float mass, Shapes::ShapeTypes type, ObjectTypes objType, std::string name, Texture& objectTexture, Material& objectMaterial, const btVector3& objectColor, const btVector3& initialPosition, const btQuaternion& initialRotation)
{
	colShape = shape;
	texture = objectTexture;
	material = objectMaterial;
	color = objectColor;

	useMaterial = true;

	scale = glm::vec3(1, 1, 1);

	initPos = initialPosition;

	this->name = name;

	shouldMove = false;

	interactable = false;

	this->objType = objType;

	if (type == Shapes::squareRepeat)
	{
		const btBoxShape* box = static_cast<const btBoxShape*>(shape);

		btVector3 halfSize = box->getHalfExtentsWithMargin();

		mesh = Shapes::SquareShapeMeshRepeatTexture(halfSize, objectColor);
	}
	else if (type == Shapes::squareStretch)
	{
		const btBoxShape* box = static_cast<const btBoxShape*>(shape);

		btVector3 halfSize = box->getHalfExtentsWithMargin();

		mesh = Shapes::SquareShapeMeshStretchTexture(halfSize, objectColor);
	}
	else if (type == Shapes::cube)
	{
		const btBoxShape* box = static_cast<const btBoxShape*>(shape);

		btVector3 halfSize = box->getHalfExtentsWithMargin();

		mesh = Shapes::CubeShapeMesh(halfSize, objectColor);
	}
	else if (type == Shapes::pyramid)
	{
		mesh = Shapes::PyramidShapeMesh(objectColor);
	}

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	motionState = new OpenGLMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0, 0, 0);

	// objects of infinite mass can't move or rotate
	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, motionState, shape, localInertia);

	// create the rigid body
	rigBody = new btRigidBody(cInfo);
}

GameObject::GameObject(Shapes::ShapeTypes type, ObjectTypes objType, const btVector3& halfSize, Texture& objectTexture, Material& objectMaterial, const btVector3& objectColor, const btVector3& initialPosition, const btQuaternion& initialRotation)
{
	texture = objectTexture;
	material = objectMaterial;
	color = objectColor;

	useMaterial = true;

	scale = glm::vec3(1, 1, 1);

	shouldMove = false;

	interactable = false;

	this->objType = objType;

	if (type == Shapes::squareRepeat)
	{
		mesh = Shapes::SquareShapeMeshRepeatTexture(halfSize, objectColor);
	}
	else if (type == Shapes::squareStretch)
	{
		mesh = Shapes::SquareShapeMeshStretchTexture(halfSize, objectColor);
	}
	else if (type == Shapes::cube)
	{
		mesh = Shapes::CubeShapeMesh(halfSize, objectColor);
	}
	else if (type == Shapes::pyramid)
	{
		mesh = Shapes::PyramidShapeMesh(objectColor);
	}

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	motionState = new OpenGLMotionState(transform);
}

GameObject::GameObject(Model& objectModel, ObjectTypes objType, std::string name, Material& objectMaterial,
	btCollisionShape* shape, float mass, const btVector3& initialPosition, const btQuaternion& initialRotation)
{
	colShape = shape;
	model = objectModel;
	this->name = name;
	mesh = nullptr;
	material = objectMaterial;

	useMaterial = true;
	changedTexture = false;

	scale = glm::vec3(1, 1, 1);

	shouldMove = false;

	interactable = false;

	this->objType = objType;

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	motionState = new OpenGLMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0, 0, 0);

	// objects of infinite mass can't move or rotate
	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, motionState, shape, localInertia);

	// create the rigid body
	rigBody = new btRigidBody(cInfo);
}

GameObject::GameObject(btCollisionShape* shape, float mass, std::string name, const btVector3& initialPosition, const btQuaternion& initialRotation)
{
	colShape = shape;

	scale = glm::vec3(1, 1, 1);

	shouldMove = false;

	interactable = false;

	this->name = name;

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	motionState = new OpenGLMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0, 0, 0);

	// objects of infinite mass can't move or rotate
	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, motionState, shape, localInertia);

	// create the rigid body
	rigBody = new btRigidBody(cInfo);
}

GameObject::~GameObject()
{
	delete rigBody;
	delete motionState;
	delete colShape;
	delete mesh;
}

void GameObject::RenderGameObject(GLuint& unifModel, GLuint& unifSpecularIntensity, GLuint& unifShininessLocation)
{
	// create an array of 16 floats (representing a 4x4 matrix)
	btScalar transformMatrix[16];
	this->GetTransform(transformMatrix);
	glm::mat4 model = HelperFunctions::btScalar2mat4(transformMatrix);

	for (int i = 0; i < rotationAxis.size(); i++)
	{
		model = glm::rotate(model, btRadians(rotationAngles[i]), rotationAxis[i]);
	}
	if (shouldMove)
	{
		model = glm::translate(model, glm::vec3(Move().getX(), Move().getY(), Move().getZ()));
	}
	model = glm::scale(model, scale);
	glUniformMatrix4fv(unifModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	if (useMaterial)
		material.UseMaterial(unifSpecularIntensity, unifShininessLocation);
	if (mesh != nullptr)
		mesh->RenderMesh();
	else
	{
		if (changedTexture)
			this->model.RenderModelWithGivenTexture(texture);
		else
			this->model.RenderModel();
	}
}

void GameObject::AddRotation(const glm::vec3& rotationAxis, float rotationAngle)
{
	this->rotationAxis.push_back(rotationAxis);
	rotationAngles.push_back(rotationAngle);
}