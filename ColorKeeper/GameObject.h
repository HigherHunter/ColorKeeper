#pragma once

#include "btBulletDynamicsCommon.h"
#include "OpenGLMotionState.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Shapes.h"
#include "HelperFunctions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:
	enum ObjectTypes { env, interactive, target };

	GameObject(
		btCollisionShape* shape, float mass,
		Shapes::ShapeTypes type, ObjectTypes objType, std::string name, Texture& objectTexture, Material& objectMaterial, const btVector3& objectColor = btVector3(1, 1, 1),
		const btVector3& initialPosition = btVector3(0, 0, 0), const btQuaternion& initialRotation = btQuaternion(0, 0, 0, 1));

	GameObject(
		Shapes::ShapeTypes type, ObjectTypes objType, const btVector3& halfSize, Texture& objectTexture, Material& objectMaterial, const btVector3& objectColor = btVector3(1, 1, 1),
		const btVector3& initialPosition = btVector3(0, 0, 0), const btQuaternion& initialRotation = btQuaternion(0, 0, 0, 1));

	GameObject(
		Model& objectModel, ObjectTypes type, std::string name, Material& objectMaterial,
		btCollisionShape* shape = nullptr, float mass = 1.0f,
		const btVector3& initialPosition = btVector3(0, 0, 0), const btQuaternion& initialRotation = btQuaternion(0, 0, 0, 1));

	GameObject(btCollisionShape* shape, float mass, std::string name,
		const btVector3& initialPosition = btVector3(0, 0, 0), const btQuaternion& initialRotation = btQuaternion(0, 0, 0, 1));

	~GameObject();

	void RenderGameObject(GLuint& unifModel, GLuint& unifSpecularIntensity, GLuint& unifShininessLocation);

	void AddRotation(const glm::vec3& rotationAxis, float rotationAngle);

	void SetScale(const glm::vec3& scale) { this->scale = scale; }

	void ChangeTexture(Texture& texture) { this->texture = texture; changedTexture = true; }

	void SetUseMaterial(bool use) { useMaterial = use; }

	btCollisionShape* GetShape() { return colShape; }
	btRigidBody* GetRigidBody() { return rigBody; }
	btMotionState* GetMotionState() { return motionState; }

	void GetTransform(btScalar* transform) { if (motionState) motionState->GetWorldTransform(transform); }

	btVector3 GetColor() { return color; }

	std::string GetName() { return name; }
	void SetName(std::string name) { this->name = name; }

	void SetShouldMove(bool move) { shouldMove = move; }

	void SetMovement(btVector3 movement) { initPos += movement; }
	btVector3 Move() { return initPos; };

	bool IsInteractable() { return interactable; }
	void SetInteractable(bool interact) { interactable = interact; }

	ObjectTypes GetObjectType() { return objType; }

protected:
	btCollisionShape* colShape;
	btRigidBody* rigBody;
	OpenGLMotionState* motionState;
	btVector3 color;
	Mesh* mesh;
	Model model;
	Texture texture;
	Material material;
	std::string name;
	ObjectTypes objType;

	btVector3 initPos;
	bool shouldMove;
	std::vector<glm::vec3> rotationAxis;
	std::vector<int> rotationAngles;
	glm::vec3 scale;

	bool useMaterial;
	bool changedTexture;

	bool interactable;
};