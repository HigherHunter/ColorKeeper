#include "PhysicsLayer.h"

PhysicsLayer::PhysicsLayer()
	:
	broadphase(0),
	collisionConfiguration(0),
	dispatcher(0),
	solver(0),
	dynamicWorld(0),
	pickedBody(0),
	pickConstraint(0)
{
	activeCell = cell1;
}

PhysicsLayer::~PhysicsLayer()
{
	ShutdownPhysics();
}

void PhysicsLayer::InitializePhysics()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	broadphase = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver();

	dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	debugDrawer = new DebugDrawer();
	debugDrawer->setDebugMode(0);
	dynamicWorld->setDebugDrawer(debugDrawer);

	//debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
	//debugDrawer->drawTexture = new Texture("Textures/plain.png");
}

void PhysicsLayer::ShutdownPhysics()
{
	delete dynamicWorld;
	delete solver;
	delete broadphase;
	delete dispatcher;
	delete collisionConfiguration;
}

void PhysicsLayer::UpdateScene()
{
	if (dynamicWorld)
	{
		// step the simulation through time. This is called every update
		dynamicWorld->stepSimulation(1.f / 60.f, 10);

		if (activeCell == cell4)
		{
			for (GameObjects::iterator iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
			{
				if (GameManager::GetInstance()->GetMistakeCount() >= 3)
				{
					(*iter)->GetRigidBody()->setGravity(btVector3(0, -1.5, 0));
				}
				else
				{
					(*iter)->GetRigidBody()->setGravity(btVector3(0, -0.8, 0));
				}
			}
		}
		// Check for any new collisions/separations
		CheckForCollisionEvents();
	}
}

void PhysicsLayer::AddObjectToPhysicsWorld(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);

	if (dynamicWorld)
	{
		dynamicWorld->addRigidBody(gameObject->GetRigidBody());
	}
}

void PhysicsLayer::DestroyGameObject(btRigidBody* body)
{
	for (GameObjects::iterator iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
	{
		if ((*iter)->GetRigidBody() == body)
		{
			GameObject* object = *iter;

			dynamicWorld->removeRigidBody(object->GetRigidBody());

			gameObjects.erase(iter);

			delete object;

			return;
		}
	}
}

void PhysicsLayer::ShootPickedObject(const btVector3& direction, btRigidBody& object)
{
	if (!pickedBody)
		return;

	btVector3 velocoty = direction;
	velocoty.normalize();
	velocoty *= 25.0f;

	RemovePickingConstraint();
	object.setLinearVelocity(velocoty);
}

bool PhysicsLayer::Raycast(const btVector3& startPosition, const btVector3& direction, RayResult& output, float multiplier)
{
	if (!dynamicWorld)
		return false;

	// ray from to inf
	btVector3 rayFrom = startPosition;
	btVector3 rayTo = direction * multiplier;

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);

	// perform the raycast
	dynamicWorld->rayTest(rayFrom, rayTo, rayCallback);
	debugRayFrom = rayFrom;
	debugRayTo = rayTo;

	if (rayCallback.hasHit())
	{
		btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);

		if (!body)
			return false;

		output.body = body;
		output.hitPoint = rayCallback.m_hitPointWorld;
		return true;
	}

	// no hit
	return false;
}

bool PhysicsLayer::CreatePickingConstraint(Camera* camera)
{
	if (!dynamicWorld)
		return false;

	RayResult output;

	if (!Raycast(camera->GetBtV3CameraPosition(), camera->GetBtV3CameraDirection(), output, 1000))
		return false; // raycast failed

	const float distance = btDistance(output.hitPoint, camera->GetBtV3CameraPosition());

	if (!FindGameObject(output.body)->IsInteractable())
		return false;

	if (distance < 1.75 || distance > 3.0)
		return false;

	pickedBody = output.body;

	// Prevent the picked object from falling asleep
	pickedBody->setActivationState(DISABLE_DEACTIVATION);

	btTransform pivot;
	pivot.setIdentity();
	pivot.setOrigin(btVector3(0, 0, 0));

	// Constraint object
	btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*pickedBody, pivot, true);

	const bool limitAngularMotion = true;

	if (limitAngularMotion)
	{
		// no rotation
		dof6->setAngularLowerLimit(btVector3(0, 0, 0));
		dof6->setAngularUpperLimit(btVector3(0, 0, 0));
	}

	dynamicWorld->addConstraint(dof6, true);

	pickConstraint = dof6;

	// Define the strength of our constraint (each axis)
	float cfm = 0.5f;
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 0);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 1);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 2);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 3);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 4);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 5);

	// Define the error reduction of our constraint (each axis)
	float erp = 0.5f;
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 0);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 1);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 2);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 3);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 4);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 5);

	oldPickingDist = (output.hitPoint - camera->GetBtV3CameraPosition()).length();

	return true;
}

void PhysicsLayer::RemovePickingConstraint()
{
	if (!pickConstraint || !dynamicWorld)
		return;

	dynamicWorld->removeConstraint(pickConstraint);

	delete pickConstraint;

	// Reactivate the body
	pickedBody->forceActivationState(ACTIVE_TAG);
	pickedBody->setDeactivationTime(0.f);

	pickConstraint = 0;
	pickedBody = 0;

	holdingObject = false;
}

bool* PhysicsLayer::CheckPlayerCollision(Camera* camera)
{
	playerAllowedMovement[0] = true;
	playerAllowedMovement[1] = true;
	playerAllowedMovement[2] = true;
	playerAllowedMovement[3] = true;

	RayResult output;

	btVector3 currentPlayerPos = camera->GetBtV3CameraPosition();
	currentPlayerPos.setY(currentPlayerPos.getY() - 1);
	btVector3 currentFrontDir = camera->GetBtV3CameraDirectionWorldUp();
	btVector3 currentRightDir = camera->GetBtV3CameraRight();

	btVector3 collisionFront = currentPlayerPos + (currentFrontDir * playerCollisionDistance);
	btVector3 collisionBack = currentPlayerPos - (currentFrontDir * playerCollisionDistance);
	btVector3 collisionRight = currentPlayerPos + (currentRightDir * playerCollisionDistance);
	btVector3 collisionLeft = currentPlayerPos - (currentRightDir * playerCollisionDistance);

	debugRayTo = collisionFront;
	debugRayTo2 = collisionBack;
	debugRayTo3 = collisionRight;
	debugRayTo4 = collisionLeft;

	if (Raycast(currentPlayerPos, collisionFront, output, 1))
	{
		if (output.body != pickedBody)
			playerAllowedMovement[0] = false;
	}
	if (Raycast(currentPlayerPos, collisionBack, output, 1))
	{
		if (output.body != pickedBody)
			playerAllowedMovement[1] = false;
	}
	if (Raycast(currentPlayerPos, collisionLeft, output, 1))
	{
		if (output.body != pickedBody)
			playerAllowedMovement[2] = false;
	}
	if (Raycast(currentPlayerPos, collisionRight, output, 1))
	{
		if (output.body != pickedBody)
			playerAllowedMovement[3] = false;
	}

	return playerAllowedMovement;
}

void PhysicsLayer::CheckForCollisionEvents()
{
	// Keep a list of the collision pairs we found during the current update
	CollisionPairs pairsThisUpdate;

	for (int i = 0; i < dispatcher->getNumManifolds(); ++i)
	{
		btPersistentManifold* manifold = dispatcher->getManifoldByIndexInternal(i);

		// Ignore manifolds that have no contact points.
		if (manifold->getNumContacts() > 0)
		{
			// Get the two rigid bodies involved in the collision
			const btRigidBody* rBody0 = static_cast<const btRigidBody*>(manifold->getBody0());
			const btRigidBody* rBody1 = static_cast<const btRigidBody*>(manifold->getBody1());

			// Always create the pair in a predictable order
			bool const swapped = rBody0 > rBody1;
			const btRigidBody* sortedBodyA = swapped ? rBody1 : rBody0;
			const btRigidBody* sortedBodyB = swapped ? rBody0 : rBody1;

			// Create the pair
			CollisionPair thisPair = std::make_pair(sortedBodyA, sortedBodyB);

			pairsThisUpdate.insert(thisPair);

			// If this pair doesn't exist in the list
			// from the previous update, it is a new
			// pair and we must send a collision event
			if (pairsLastUpdate.find(thisPair) == pairsLastUpdate.end())
				CollisionEvent((btRigidBody*)rBody0, (btRigidBody*)rBody1);
		}
	}

	// Create another list for pairs that were removed this update
	CollisionPairs removedPairs;

	// Difference between collision pairs from the last update, and this update and push them into the removed pairs list
	std::set_difference(pairsLastUpdate.begin(), pairsLastUpdate.end(),
		pairsThisUpdate.begin(), pairsThisUpdate.end(),
		std::inserter(removedPairs, removedPairs.begin()));

	// Iterate through removed pairs ending separation events
	for (CollisionPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter)
	{
		SeparationEvent((btRigidBody*)iter->first, (btRigidBody*)iter->second);
	}

	// Pairs for comparison
	pairsLastUpdate = pairsThisUpdate;
}

void PhysicsLayer::CollisionEvent(btRigidBody* rBody0, btRigidBody* rBody1)
{
	// Find the two colliding objects
	GameObject* obj0 = FindGameObject(rBody0);
	GameObject* obj1 = FindGameObject(rBody1);

	// Exit
	if (!obj0 || !obj1) return;

	if (holdingObject && (rBody0 == pickedBody || rBody1 == pickedBody))
	{
	}
	else
	{
		if (activeCell == cell1)
		{
			if (obj0->GetName() == "pedestalCell1" && obj1->GetName() == "woodBox")
			{
				obj1->SetInteractable(false);
				DestroyGameObject(FindGameObjectByName("gateCell1")->GetRigidBody());
				activeCell = cell2;
				cell2Check = 0;
				SoundManager::GetInstance()->PlayCorrectSound();
			}
		}
		else if (activeCell == cell2)
		{
			if (obj0->GetObjectType() == GameObject::target && obj1->GetObjectType() == GameObject::interactive)
			{
				if (obj0->GetName() == "pedestal1Cell2" && obj1->GetName() == "RedBox")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell2Check++;
					if (cell2Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell2")->GetRigidBody());
						activeCell = cell3;
						cell2Check = 0;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj0->GetName() == "pedestal2Cell2" && obj1->GetName() == "GreenBox")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell2Check++;
					if (cell2Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell2")->GetRigidBody());
						activeCell = cell3;
						cell2Check = 0;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj0->GetName() == "pedestal3Cell2" && obj1->GetName() == "BlueBox")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell2Check++;
					if (cell2Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell2")->GetRigidBody());
						activeCell = cell3;
						cell2Check = 0;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj0->GetName() == "pedestal4Cell2" && obj1->GetName() == "YellowBox")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell2Check++;
					if (cell2Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell2")->GetRigidBody());
						activeCell = cell3;
						cell2Check = 0;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else
				{
					SoundManager::GetInstance()->PlayErrorSound();
				}
			}
		}
		else if (activeCell == cell3)
		{
			if (obj0->GetObjectType() == GameObject::target && obj1->GetObjectType() == GameObject::interactive)
			{
				if (obj1->GetName() == "techBox1")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell3Check++;
					if (cell3Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell3")->GetRigidBody());
						activeCell = cell4;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj1->GetName() == "techBox2")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell3Check++;
					if (cell3Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell3")->GetRigidBody());
						activeCell = cell4;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj1->GetName() == "techBox3")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell3Check++;
					if (cell3Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell3")->GetRigidBody());
						activeCell = cell4;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
				else if (obj1->GetName() == "techBox4")
				{
					obj1->SetInteractable(false);
					obj1->SetName("");
					cell3Check++;
					if (cell3Check == 4)
					{
						DestroyGameObject(FindGameObjectByName("gateCell3")->GetRigidBody());
						activeCell = cell4;
						cell3Check = 0;
					}
					SoundManager::GetInstance()->PlayCorrectSound();
				}
			}
		}
		else if (activeCell == cell4)
		{
			if (obj0->GetName() == "destroy" || obj0->GetName() == "destroy2")
				DestroyGameObject(obj1->GetRigidBody());
			else
			{
				if (obj0->GetObjectType() == GameObject::interactive && obj1->GetObjectType() == GameObject::target)
				{
					if (obj0->GetName() == "rBp" && obj1->GetName() == "rB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "gBp" && obj1->GetName() == "gB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "bBp" && obj1->GetName() == "bB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "yBp" && obj1->GetName() == "yB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "pBp" && obj1->GetName() == "pB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "cBp" && obj1->GetName() == "cB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "oBp" && obj1->GetName() == "oB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else if (obj0->GetName() == "grBp" && obj1->GetName() == "grB")
					{
						SoundManager::GetInstance()->PlayCorrectSound();
						GameManager::GetInstance()->IncreaseScore(100);
					}
					else
					{
						SoundManager::GetInstance()->PlayErrorSound();
						GameManager::GetInstance()->ProcessMistake(100);
					}
				}
			}
		}
	}
}

void PhysicsLayer::SeparationEvent(btRigidBody* rBody0, btRigidBody* rBody1)
{
	// Get the two separating objects
	GameObject* obj0 = FindGameObject((btRigidBody*)rBody0);
	GameObject* obj1 = FindGameObject((btRigidBody*)rBody1);

	// Exit
	if (!obj0 || !obj1) return;
}

GameObject* PhysicsLayer::FindGameObject(btRigidBody* rBody)
{
	// Search for object 
	for (GameObjects::iterator iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
	{
		if ((*iter)->GetRigidBody() == rBody)
		{
			// Found the body, return
			return *iter;
		}
	}
	return 0;
}

GameObject* PhysicsLayer::FindGameObjectByName(std::string name)
{
	// Search for object 
	for (GameObjects::iterator iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
	{
		if ((*iter)->GetName() == name)
		{
			// Found the name, return
			return *iter;
		}
	}
	return 0;
}