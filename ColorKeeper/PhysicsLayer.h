#pragma once

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#include <vector>
#include <set>
#include <iterator>
#include "GameObject.h"
#include "Camera.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "DebugDrawer.h"

typedef std::vector<GameObject*> GameObjects;
// typedefs for collision events
typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
typedef std::set<CollisionPair> CollisionPairs;

// struct for raycast results
struct  RayResult
{
	btRigidBody* body;
	btVector3 hitPoint;
};

class PhysicsLayer
{
public:
	enum Cells { cell1, cell2, cell3, cell4, cellEnd };

	PhysicsLayer();
	~PhysicsLayer();

	void InitializePhysics();
	void ShutdownPhysics();

	void UpdateScene();

	// Game objects functions
	void AddObjectToPhysicsWorld(GameObject* gameObject);
	void DestroyGameObject(btRigidBody* body);
	void ShootPickedObject(const btVector3& direction, btRigidBody& object);

	bool Raycast(const btVector3& startPosition, const btVector3& direction, RayResult& output, float multiplier);

	// Constraint functions
	bool CreatePickingConstraint(Camera* camera);
	void RemovePickingConstraint();

	// Player collision func
	bool* CheckPlayerCollision(Camera* camera);

	btDynamicsWorld* GetDynamicWorld() { return dynamicWorld; }
	DebugDrawer* GetDebugDrawer() { return debugDrawer; }
	btVector3 GetDebugRayFrom() { return debugRayFrom; }
	btVector3 GetDebugRayTo() { return debugRayTo; }
	btVector3 GetDebugRayTo2() { return debugRayTo2; }
	btVector3 GetDebugRayTo3() { return debugRayTo3; }
	btVector3 GetDebugRayTo4() { return debugRayTo4; }

	btRigidBody* GetPickedBody() { return pickedBody; }
	btTypedConstraint* GetPickConstraint() { return pickConstraint; }
	btScalar GetOldPickingDistance() { return oldPickingDist; }

	bool IsHoldingObject() { return holdingObject; }
	void SetHolding(bool holding) { holdingObject = holding; }

	// Array of game objects
	GameObjects gameObjects;

	GameObject* FindGameObject(btRigidBody* rBody);
	GameObject* FindGameObjectByName(std::string name);

	Cells GetActiveCell() { return activeCell; }
	void SetActiveCell(Cells cell) { activeCell = cell; }

protected:

	int cell2Check, cell3Check;

	Cells activeCell;

	// Physics components
	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver* solver;
	btDynamicsWorld* dynamicWorld;

	btClock clock;

	// debug renderer
	DebugDrawer* debugDrawer;

	btVector3 debugRayFrom, debugRayTo, debugRayTo2, debugRayTo3, debugRayTo4;

	bool holdingObject = false;
	btRigidBody* pickedBody;
	// Constraint the body is attached to
	btTypedConstraint* pickConstraint;
	// Distance from camera to hit point for movement
	btScalar oldPickingDist;

	float playerCollisionDistance = 1.0f;
	bool playerAllowedMovement[4];

	// Collision event variables
	CollisionPairs pairsLastUpdate;

	// Collision event functions
	void CheckForCollisionEvents();
	virtual void CollisionEvent(btRigidBody* rBody0, btRigidBody* rBody1);
	virtual void SeparationEvent(btRigidBody* rBody0, btRigidBody* rBody1);
};