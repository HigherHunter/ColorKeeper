#include "SceneManager.h"

SceneManager::SceneManager()
{
	// Materials
	dullMaterial = Material(0.3f, 4);
	shinyMaterial = Material(4.0f, 256);

	// Textures
	groundCobblestoneTexture = Texture("Assets/Textures/Ground/Cobblestone.png");
	groundCobblestoneTexture.LoadTexture(GL_REPEAT);

	brick = Texture("Assets/Textures/Brick.jpg");
	brick.LoadTexture(GL_REPEAT);

	floorSquares = Texture("Assets/Textures/Ground/Floor_squares.png");
	floorSquares.LoadTextureWithAlpha(GL_REPEAT);

	rustTexture = Texture("Assets/Textures/rust.jpg");
	rustTexture.LoadTexture(GL_REPEAT);

	squareTechTexture1 = Texture("Assets/Textures/Squares/sq1.png");
	squareTechTexture1.LoadTextureWithAlpha(GL_CLAMP);

	squareTechTexture2 = Texture("Assets/Textures/Squares/sq2.png");
	squareTechTexture2.LoadTextureWithAlpha(GL_CLAMP);

	squareTechTexture3 = Texture("Assets/Textures/Squares/sq4.png");
	squareTechTexture3.LoadTextureWithAlpha(GL_CLAMP);

	squareTechTexture4 = Texture("Assets/Textures/Squares/sq5.png");
	squareTechTexture4.LoadTextureWithAlpha(GL_CLAMP);

	sandWhite = Texture("Assets/Textures/sand_white.png");
	sandWhite.LoadTextureWithAlpha(GL_CLAMP);

	screen1 = Texture("Assets/Textures/Texts/screen1.png");
	screen1.LoadTexture(GL_CLAMP);

	screen2 = Texture("Assets/Textures/Texts/screen2.png");
	screen2.LoadTexture(GL_CLAMP);

	screen3 = Texture("Assets/Textures/Texts/screen3.png");
	screen3.LoadTexture(GL_CLAMP);

	screen4 = Texture("Assets/Textures/Texts/screen4.png");
	screen4.LoadTexture(GL_CLAMP);

	// Models
	cube = Model();
	cube.LoadModel("Assets/Models/Crate1.obj", false);

	rustyGate = Model();
	rustyGate.LoadModel("Assets/Models/fence01.obj", false);

	chandelier = Model();
	chandelier.LoadModel("Assets/Models/Lamp150 (OBJ).obj", false);

	techPedestal = Model();
	techPedestal.LoadModel("Assets/Models/tech_pedestal.obj", false);

	dispenserExport = Model();
	dispenserExport.LoadModel("Assets/Models/dispenser_export.obj", false);

	Arch = Model();
	Arch.LoadModel("Assets/Models/Castle/Arch.FBX", false);

	Brick_Wall = Model();
	Brick_Wall.LoadModel("Assets/Models/Castle/Brick_Wall.FBX", false);

	Cathedral_Window = Model();
	Cathedral_Window.LoadModel("Assets/Models/Castle/Cathedral_Window.FBX", false);

	Cornice = Model();
	Cornice.LoadModel("Assets/Models/Castle/Cornice.FBX", false);

	Door = Model();
	Door.LoadModel("Assets/Models/Castle/Door.FBX", false);

	Narrow_Pillar = Model();
	Narrow_Pillar.LoadModel("Assets/Models/Castle/Narrow_Pillar.FBX", false);

	Pillar_Standalone = Model();
	Pillar_Standalone.LoadModel("Assets/Models/Castle/Pillar_Standalone.FBX", false);

	Wide_Pillar_No_Door = Model();
	Wide_Pillar_No_Door.LoadModel("Assets/Models/Castle/Wide_Pillar_No_Door.FBX", false);

	Wide_Pillar_With_Door = Model();
	Wide_Pillar_With_Door.LoadModel("Assets/Models/Castle/Wide_Pillar_With_Door.FBX", false);

	Windows = Model();
	Windows.LoadModel("Assets/Models/Castle/Windows.FBX", false);

	Switch_round_button = Model();
	Switch_round_button.LoadModel("Assets/Models/switch_round_button.FBX", false);

	physicsWorld = new PhysicsLayer();
	physicsWorld->InitializePhysics();

	cell1Built = false, cell2Built = false, cell3Built = false, cell4Built = false;
	cell1Deleted = false, cell2Deleted = false, cell3Deleted = false;
}

void SceneManager::BuildCell1()
{
	// FLOOR
	GameObject* floor = new GameObject(new btBoxShape(btVector3(10, 0, 10)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("FloorCell1"), groundCobblestoneTexture, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 0.0f, 0.0f));
	physicsWorld->AddObjectToPhysicsWorld(floor);
	cell1GameObjects.push_back(floor);

	// Roof
	GameObject* roof = new GameObject(new btBoxShape(btVector3(15, 0, 4)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("RoofCell1"), brick, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 5.0f, 7.0f));
	roof->AddRotation(glm::vec3(1, 0, 0), -180);
	physicsWorld->AddObjectToPhysicsWorld(roof);
	cell1GameObjects.push_back(roof);

	// SCREEN 1
	GameObject* screen = new GameObject(new btBoxShape(btVector3(1.5, 0, 1.5)), 0.0f, Shapes::squareStretch, GameObject::env, std::string("Screen1"), screen1, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(-4.0f, 2.0f, -9.4f));
	screen->AddRotation(glm::vec3(1, 0, 0), 90);
	nonPhysicsGameObjects.push_back(screen);
	cell1GameObjects.push_back(screen);

	// Chandelier left
	GameObject* chandelierLeft = new GameObject(chandelier, GameObject::env, "", shinyMaterial, new btBoxShape(btVector3(0.75, 0.75, 0.75)), 0.0f, btVector3(-6.0f, 3.4f, 7.0f));
	chandelierLeft->SetScale(glm::vec3(0.2, 0.2, 0.2));
	chandelierLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(chandelierLeft);
	cell1GameObjects.push_back(chandelierLeft);
	chandelierLeft->SetShouldMove(true);
	chandelierLeft->SetMovement(btVector3(0, -1, 0.75));

	// Chandelier right
	GameObject* chandelierRight = new GameObject(chandelier, GameObject::env, "", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(6.0f, 3.4f, 7.0f));
	chandelierRight->SetScale(glm::vec3(0.2, 0.2, 0.2));
	chandelierRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(chandelierRight);
	cell1GameObjects.push_back(chandelierRight);
	chandelierRight->SetShouldMove(true);
	chandelierRight->SetMovement(btVector3(0, -1, 0.75));

	// Arch
	GameObject* arch = new GameObject(Arch, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-1.5f, 0.0f, -10.0f));
	arch->SetScale(glm::vec3(0.005, 0.005, 0.005));
	arch->AddRotation(glm::vec3(1, 0, 0), -90);
	arch->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(arch);
	cell2GameObjects.push_back(arch);

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell1", dullMaterial, new btBoxShape(btVector3(1.4, 2.0, 0.5)), 0.0f, btVector3(-0.075f, 2.0f, -9.75f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->SetUseMaterial(false);
	gate->ChangeTexture(rustTexture);
	physicsWorld->AddObjectToPhysicsWorld(gate);

	// Brick Wall back left
	GameObject* brickWallBackLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-10.0f, 0.0f, 10.0f));
	brickWallBackLeft->SetScale(glm::vec3(0.009, 0.008, 0.00675));
	brickWallBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallBackLeft->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallBackLeft);
	cell1GameObjects.push_back(brickWallBackLeft);

	// Brick Wall back right
	GameObject* brickWallBackRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(1.4f, 0.0f, 10.0f));
	brickWallBackRight->SetScale(glm::vec3(0.009, 0.008, 0.00675));
	brickWallBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallBackRight->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallBackRight);
	cell1GameObjects.push_back(brickWallBackRight);

	// Brick Wall front left
	GameObject* brickWallFrontLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-10.0f, 0.0f, -10.0f));
	brickWallFrontLeft->SetScale(glm::vec3(0.009, 0.008, 0.00675));
	brickWallFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontLeft->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallFrontLeft);
	cell2GameObjects.push_back(brickWallFrontLeft);

	// Brick Wall front right
	GameObject* brickWallFrontRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(1.4f, 0.0f, -10.0f));
	brickWallFrontRight->SetScale(glm::vec3(0.009, 0.008, 0.00675));
	brickWallFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontRight->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallFrontRight);
	cell2GameObjects.push_back(brickWallFrontRight);

	// Door
	GameObject* door = new GameObject(Door, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(12.0, 5.0, 0.1)), 0.0f, btVector3(-1.5f, 0.0f, 10.0f));
	door->SetScale(glm::vec3(0.005, 0.005, 0.005));
	door->AddRotation(glm::vec3(1, 0, 0), -90);
	door->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(door);
	cell1GameObjects.push_back(door);
	//nonPhysicsGameObjects.push_back(door);

	// Windows left
	GameObject* windowsLeft = new GameObject(Windows, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 12.0)), 0.0f, btVector3(-10.0f, 0.0f, 2.475f));
	windowsLeft->SetScale(glm::vec3(0.0055, 0.005, 0.00675));
	windowsLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsLeft->AddRotation(glm::vec3(0, 0, 1), 90);
	windowsLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(windowsLeft);
	cell1GameObjects.push_back(windowsLeft);
	//nonPhysicsGameObjects.push_back(windowsLeft);

	// Left windows pillar front
	GameObject* pillarLeftFront = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-11.0f, 0.0f, 2.5f));
	pillarLeftFront->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarLeftFront->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarLeftFront->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(pillarLeftFront);
	cell1GameObjects.push_back(pillarLeftFront);

	// Left windows pillar back
	GameObject* pillarLeftBack = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-11.0f, 0.0f, -5.0f));
	pillarLeftBack->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarLeftBack->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarLeftBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(pillarLeftBack);
	cell1GameObjects.push_back(pillarLeftBack);

	// Brick Wall left front
	GameObject* brickWallLeftFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-10.0f, 0.0f, -5.0f));
	brickWallLeftFront->SetScale(glm::vec3(0.005, 0.008, 0.00675));
	brickWallLeftFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallLeftFront->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallLeftFront->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallLeftFront);
	cell1GameObjects.push_back(brickWallLeftFront);

	// Brick Wall left back
	GameObject* brickWallLeftBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-10.0f, 0.0f, 10.0f));
	brickWallLeftBack->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallLeftBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallLeftBack->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallLeftBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallLeftBack);
	cell1GameObjects.push_back(brickWallLeftBack);

	// Windows right
	GameObject* windowsRight = new GameObject(Windows, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 12.0)), 0.0f, btVector3(10.0f, 0.0f, 2.475f));
	windowsRight->SetScale(glm::vec3(0.0055, 0.005, 0.00675));
	windowsRight->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsRight->AddRotation(glm::vec3(0, 0, 1), 90);
	windowsRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(windowsRight);
	cell1GameObjects.push_back(windowsRight);

	// Right windows pillar front
	GameObject* pillarRightFront = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(9.5f, 0.0f, 2.5f));
	pillarRightFront->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarRightFront->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarRightFront->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(pillarRightFront);
	cell1GameObjects.push_back(pillarRightFront);

	// Right windows pillar back
	GameObject* pillarRightBack = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(9.5f, 0.0f, -5.0f));
	pillarRightBack->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarRightBack->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarRightBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(pillarRightBack);
	cell1GameObjects.push_back(pillarRightBack);

	// Brick Wall right front
	GameObject* brickWallRightFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(10.0f, 0.0f, -5.0f));
	brickWallRightFront->SetScale(glm::vec3(0.005, 0.008, 0.00675));
	brickWallRightFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightFront->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallRightFront->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallRightFront);
	cell1GameObjects.push_back(brickWallRightFront);

	// Brick Wall right back
	GameObject* brickWallRightBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(10.0f, 0.0f, 10.0f));
	brickWallRightBack->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallRightBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightBack->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallRightBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallRightBack);
	cell1GameObjects.push_back(brickWallRightBack);

	// Pedestal
	GameObject* pedestal = new GameObject(techPedestal, GameObject::env, "pedestalCell1", dullMaterial, new btBoxShape(btVector3(1.0, 0.25, 1.0)), 0.0f, btVector3(3.5f, 0.0f, -7.5f));
	pedestal->SetScale(glm::vec3(0.1, 0.1, 0.1));
	pedestal->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pedestal);
	cell1GameObjects.push_back(pedestal);

	pedestal->ChangeTexture(squareTechTexture4);

	// Wood box
	GameObject* woodBox = new GameObject(cube, GameObject::interactive, "woodBox", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, btVector3(0.0f, 0.5f, 0.0f));
	woodBox->SetScale(glm::vec3(0.5, 0.5, 0.5));
	woodBox->SetInteractable(true);
	physicsWorld->AddObjectToPhysicsWorld(woodBox);
	cell1GameObjects.push_back(woodBox);
}

void SceneManager::BuildCell2()
{
	// FLOOR
	GameObject* floor = new GameObject(new btBoxShape(btVector3(15, 0, 15)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("FloorCell2"), groundCobblestoneTexture, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 0.0f, -25.0f));
	physicsWorld->AddObjectToPhysicsWorld(floor);
	cell2GameObjects.push_back(floor);

	// Roof
	GameObject* roof = new GameObject(new btBoxShape(btVector3(10, 0, 4)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("RoofCell2"), brick, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 5.5f, -19.0f));
	roof->AddRotation(glm::vec3(1, 0, 0), -180);
	physicsWorld->AddObjectToPhysicsWorld(roof);
	cell2GameObjects.push_back(roof);

	// Roof 2
	GameObject* roof2 = new GameObject(new btBoxShape(btVector3(10, 0, 4)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("RoofCell2"), brick, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 5.5f, -34.0f));
	roof2->AddRotation(glm::vec3(1, 0, 0), -180);
	physicsWorld->AddObjectToPhysicsWorld(roof2);
	cell2GameObjects.push_back(roof2);

	// Pillar front right
	GameObject* pillarFrontRight = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(6.0f, 0.0f, -34.0f));
	pillarFrontRight->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarFrontRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pillarFrontRight);
	cell2GameObjects.push_back(pillarFrontRight);
	pillarFrontRight->SetShouldMove(true);
	pillarFrontRight->SetMovement(btVector3(-1.0, 1.0, 0.0));

	// Pillar back right
	GameObject* pillarBackRight = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(6.0f, 0.0f, -19.0f));
	pillarBackRight->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarBackRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pillarBackRight);
	cell2GameObjects.push_back(pillarBackRight);
	pillarBackRight->SetShouldMove(true);
	pillarBackRight->SetMovement(btVector3(-1.0, 1.0, 0.0));

	// Pillar front left
	GameObject* pillarFrontLeft = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(-6.0f, 0.0f, -34.0f));
	pillarFrontLeft->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarFrontLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pillarFrontLeft);
	cell2GameObjects.push_back(pillarFrontLeft);
	pillarFrontLeft->SetShouldMove(true);
	pillarFrontLeft->SetMovement(btVector3(-1.0, 1.0, 0.0));

	// Pillar back left
	GameObject* pillarBackLeft = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(-6.0f, 0.0f, -19.0f));
	pillarBackLeft->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarBackLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pillarBackLeft);
	cell2GameObjects.push_back(pillarBackLeft);
	pillarBackLeft->SetShouldMove(true);
	pillarBackLeft->SetMovement(btVector3(-1.0, 1.0, 0.0));

	// Arch
	GameObject* arch = new GameObject(Arch, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(15.0f, 0.0f, -23.5f));
	arch->SetScale(glm::vec3(0.005, 0.005, 0.005));
	arch->AddRotation(glm::vec3(1, 0, 0), -90);
	arch->AddRotation(glm::vec3(0, 0, 1), 90);
	arch->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(arch);
	cell3GameObjects.push_back(arch);

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell2", dullMaterial, new btBoxShape(btVector3(0.5, 2.0, 1.4)), 0.0f, btVector3(15.25f, 2.0f, -24.85f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->AddRotation(glm::vec3(0, 1, 0), 90);
	gate->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(gate);
	gate->ChangeTexture(rustTexture);

	// Cathedral Window back left
	GameObject* windowsBackLeft = new GameObject(Cathedral_Window, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(14.0, 5.0, 0.25)), 0.0f, btVector3(-15.2f, -0.02f, -10.0f));
	windowsBackLeft->SetScale(glm::vec3(0.009, 0.005, 0.0051));
	windowsBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsBackLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(windowsBackLeft);
	cell2GameObjects.push_back(windowsBackLeft);

	// Cathedral Window back right
	GameObject* windowBackRight = new GameObject(Cathedral_Window, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(9.0, 5.0, 0.25)), 0.0f, btVector3(10.0f, 0.0f, -10.0f));
	windowBackRight->SetScale(glm::vec3(0.009, 0.005, 0.005));
	windowBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	windowBackRight->SetUseMaterial(false);
	//nonPhysicsGameObjects.push_back(windowBackRight);
	physicsWorld->AddObjectToPhysicsWorld(windowBackRight);
	cell2GameObjects.push_back(windowBackRight);

	// Windows front
	GameObject* windowsFront = new GameObject(Windows, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(30.0, 5.0, 0.5)), 0.0f, btVector3(-2.1f, 0.0f, -40.0f));
	windowsFront->SetScale(glm::vec3(0.00577, 0.005, 0.00675));
	windowsFront->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsFront->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(windowsFront);
	cell2GameObjects.push_back(windowsFront);

	// Brick Wall right back
	GameObject* brickWallRightBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 13.25)), 0.0f, btVector3(15.0f, 0.0f, -10.0f));
	brickWallRightBack->SetScale(glm::vec3(0.01415, 0.008, 0.00675));
	brickWallRightBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightBack->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallRightBack->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(brickWallRightBack);
	cell3GameObjects.push_back(brickWallRightBack);

	// Brick Wall right front
	GameObject* brickWallRightFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.25, 5.0, 13.25)), 0.0f, btVector3(15.5f, 0.0f, -39.75f));
	brickWallRightFront->SetScale(glm::vec3(0.014, 0.008, 0.00675));
	brickWallRightFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightFront->AddRotation(glm::vec3(0, 0, 1), 270);
	brickWallRightFront->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(brickWallRightFront);
	cell3GameObjects.push_back(brickWallRightFront);

	// Brick Wall left back
	GameObject* brickWallLeftBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-15.0f, 0.0f, -10.0f));
	brickWallLeftBack->SetScale(glm::vec3(0.0155, 0.008, 0.00675));
	brickWallLeftBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallLeftBack->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallLeftBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallLeftBack);
	cell2GameObjects.push_back(brickWallLeftBack);

	// Brick Wall left front
	GameObject* brickWallLeftFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 15.0)), 0.0f, btVector3(-15.0f, 0.0f, -24.875f));
	brickWallLeftFront->SetScale(glm::vec3(0.016, 0.008, 0.00675));
	brickWallLeftFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallLeftFront->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallLeftFront->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(brickWallLeftFront);
	cell2GameObjects.push_back(brickWallLeftFront);

	// Brick Wall front left
	GameObject* brickWallFrontLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(-15.0f, 0.0f, -40.0f));
	brickWallFrontLeft->SetScale(glm::vec3(0.0135, 0.008, 0.00675));
	brickWallFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontLeft->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallFrontLeft);
	cell2GameObjects.push_back(brickWallFrontLeft);

	// Brick Wall front right
	GameObject* brickWallFrontRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(3.5f, 0.0f, -40.0f));
	brickWallFrontRight->SetScale(glm::vec3(0.012, 0.008, 0.00675));
	brickWallFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontRight->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(brickWallFrontRight);
	cell2GameObjects.push_back(brickWallFrontRight);

	// Pedestal front left
	GameObject* pedestalFrontLeft = new GameObject(techPedestal, GameObject::target, "pedestal1Cell2", dullMaterial, new btBoxShape(btVector3(1.0, 0.25, 1.0)), 0.0f, btVector3(-8.5f, 0.0f, -34.0f));
	pedestalFrontLeft->SetScale(glm::vec3(0.1, 0.1, 0.1));
	pedestalFrontLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pedestalFrontLeft);
	cell2GameObjects.push_back(pedestalFrontLeft);
	pedestalFrontLeft->ChangeTexture(squareTechTexture4);

	// Pedestal back left
	GameObject* pedestalBackLeft = new GameObject(techPedestal, GameObject::target, "pedestal2Cell2", dullMaterial, new btBoxShape(btVector3(1.0, 0.25, 1.0)), 0.0f, btVector3(-8.5f, 0.0f, -19.0f));
	pedestalBackLeft->SetScale(glm::vec3(0.1, 0.1, 0.1));
	pedestalBackLeft->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pedestalBackLeft);
	cell2GameObjects.push_back(pedestalBackLeft);
	pedestalBackLeft->ChangeTexture(squareTechTexture4);

	// Pedestal front right
	GameObject* pedestalFrontRight = new GameObject(techPedestal, GameObject::target, "pedestal3Cell2", dullMaterial, new btBoxShape(btVector3(1.0, 0.25, 1.0)), 0.0f, btVector3(8.75f, 0.0f, -34.0f));
	pedestalFrontRight->SetScale(glm::vec3(0.1, 0.1, 0.1));
	pedestalFrontRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pedestalFrontRight);
	cell2GameObjects.push_back(pedestalFrontRight);
	pedestalFrontRight->ChangeTexture(squareTechTexture4);

	// Pedestal back back
	GameObject* pedestalBackRight = new GameObject(techPedestal, GameObject::target, "pedestal4Cell2", dullMaterial, new btBoxShape(btVector3(1.0, 0.25, 1.0)), 0.0f, btVector3(8.75f, 0.0f, -19.0f));
	pedestalBackRight->SetScale(glm::vec3(0.1, 0.1, 0.1));
	pedestalBackRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(pedestalBackRight);
	cell2GameObjects.push_back(pedestalBackRight);
	pedestalBackRight->ChangeTexture(squareTechTexture4);

	GameObject* redBox = new GameObject(new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, Shapes::cube, GameObject::interactive, std::string("RedBox"), sandWhite, shinyMaterial, btVector3(1.0f, 0.0f, 0.0f), btVector3(-1.0f, 0.5f, -30.0f));
	physicsWorld->AddObjectToPhysicsWorld(redBox);
	cell2GameObjects.push_back(redBox);
	redBox->SetInteractable(true);

	GameObject* greenBox = new GameObject(new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, Shapes::cube, GameObject::interactive, std::string("GreenBox"), sandWhite, shinyMaterial, btVector3(0.0f, 1.0f, 0.0f), btVector3(1.0f, 0.5f, -30.0f));
	physicsWorld->AddObjectToPhysicsWorld(greenBox);
	cell2GameObjects.push_back(greenBox);
	greenBox->SetInteractable(true);

	GameObject* blueBox = new GameObject(new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, Shapes::cube, GameObject::interactive, std::string("BlueBox"), sandWhite, shinyMaterial, btVector3(0.0f, 0.0f, 1.0f), btVector3(0.0f, 0.5f, -31.0f));
	physicsWorld->AddObjectToPhysicsWorld(blueBox);
	cell2GameObjects.push_back(blueBox);
	blueBox->SetInteractable(true);

	GameObject* yellowBox = new GameObject(new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, Shapes::cube, GameObject::interactive, std::string("YellowBox"), sandWhite, shinyMaterial, btVector3(1.0f, 1.0f, 0.0f), btVector3(0.0f, 0.5f, -29.0f));
	physicsWorld->AddObjectToPhysicsWorld(yellowBox);
	cell2GameObjects.push_back(yellowBox);
	yellowBox->SetInteractable(true);

	GameObject* roofBlock = new GameObject(new btBoxShape(btVector3(15.0, 0.25, 25.0)), 0.0f, "", btVector3(0, 5, -15));
	physicsWorld->AddObjectToPhysicsWorld(roofBlock);
	cell2GameObjects.push_back(roofBlock);
}

void SceneManager::BuildCell3()
{
	// FLOOR
	GameObject* floor = new GameObject(new btBoxShape(btVector3(10, 0, 15)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("FloorCell3"), floorSquares, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(25.0f, 0.0f, -25.0f));
	physicsWorld->AddObjectToPhysicsWorld(floor);
	cell3GameObjects.push_back(floor);

	// Roof
	GameObject* roof = new GameObject(new btBoxShape(btVector3(10, 0, 15)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("RoofCell3"), brick, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(25.0f, 5.0f, -25.0f));
	roof->AddRotation(glm::vec3(1, 0, 0), -180);
	physicsWorld->AddObjectToPhysicsWorld(roof);
	cell3GameObjects.push_back(roof);

	// SCREEN 2
	GameObject* screen = new GameObject(new btBoxShape(btVector3(1.5, 0, 1.5)), 0.0f, Shapes::squareStretch, GameObject::env, std::string("Screen2"), screen2, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(22.4f, 2.0f, -25.25f));
	screen->AddRotation(glm::vec3(1, 0, 0), 90);
	screen->AddRotation(glm::vec3(0, 0, 1), 90);
	nonPhysicsGameObjects.push_back(screen);
	cell3GameObjects.push_back(screen);

	// Arch
	GameObject* arch = new GameObject(Arch, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(35.0f, 0.0f, -23.5f));
	arch->SetScale(glm::vec3(0.005, 0.005, 0.005));
	arch->AddRotation(glm::vec3(1, 0, 0), -90);
	arch->AddRotation(glm::vec3(0, 0, 1), 90);
	arch->SetUseMaterial(true);
	nonPhysicsGameObjects.push_back(arch);
	cell4GameObjects.push_back(roof);

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell3", dullMaterial, new btBoxShape(btVector3(0.5, 2.0, 1.4)), 0.0f, btVector3(35.25f, 2.0f, -24.85f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->AddRotation(glm::vec3(0, 1, 0), 90);
	gate->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gate);
	gate->ChangeTexture(rustTexture);

	// Pillar middle
	GameObject* pillarMiddle = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(2.2, 5.0, 2.3)), 0.0f, btVector3(24.7f, 0.0f, -25.3f));
	pillarMiddle->SetScale(glm::vec3(0.01, 0.01, 0.0055));
	pillarMiddle->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarMiddle->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarMiddle);
	cell3GameObjects.push_back(pillarMiddle);
	pillarMiddle->SetShouldMove(true);
	pillarMiddle->SetMovement(btVector3(-2.2, 2.2, 0.0));

	// LEFT FRONT CORNER

	// Gate left front corner 1
	GameObject* gateLeftFront1 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(2.0, 1.5, 0.15)), 0.0f, btVector3(17.0f, 2.0f, -35.0f));
	gateLeftFront1->SetScale(glm::vec3(0.0075, 0.020, 0.01));
	gateLeftFront1->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateLeftFront1);
	cell3GameObjects.push_back(gateLeftFront1);
	gateLeftFront1->ChangeTexture(rustTexture);

	// Gate left front corner 2
	GameObject* gateLeftFront2 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.15, 1.5, 2.0)), 0.0f, btVector3(19.0f, 2.0f, -37.25f));
	gateLeftFront2->SetScale(glm::vec3(0.01, 0.020, 0.01));
	gateLeftFront2->AddRotation(glm::vec3(0, 1, 0), 90);
	gateLeftFront2->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateLeftFront2);
	cell3GameObjects.push_back(gateLeftFront2);
	gateLeftFront2->ChangeTexture(rustTexture);

	// Pillar left front
	GameObject* pillarLeftFront = new GameObject(Narrow_Pillar, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 0.5)), 0.0f, btVector3(19.0f, 0.0f, -35.0f));
	pillarLeftFront->SetScale(glm::vec3(0.004, 0.005, 0.007));
	pillarLeftFront->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarLeftFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarLeftFront);
	cell3GameObjects.push_back(pillarLeftFront);
	pillarLeftFront->SetShouldMove(true);
	pillarLeftFront->SetMovement(btVector3(-0.5, 0.25, 0.0));

	// Pedestal left front
	GameObject* pedestalLeftFront = new GameObject(techPedestal, GameObject::target, "pedestalTech2", dullMaterial, new btBoxShape(btVector3(1.8, 0.25, 1.8)), 0.0f, btVector3(17.25f, 0.0f, -37.5f));
	pedestalLeftFront->SetScale(glm::vec3(0.15, 0.1, 0.15));
	pedestalLeftFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pedestalLeftFront);
	cell3GameObjects.push_back(pedestalLeftFront);
	pedestalLeftFront->ChangeTexture(squareTechTexture2);

	// RIGHT FRONT CORNER

	// Gate right front corner 1
	GameObject* gateRightFront1 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(2.0, 1.5, 0.15)), 0.0f, btVector3(33.5f, 2.0f, -35.0f));
	gateRightFront1->SetScale(glm::vec3(0.0075, 0.020, 0.01));
	gateRightFront1->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateRightFront1);
	cell3GameObjects.push_back(gateRightFront1);
	gateRightFront1->ChangeTexture(rustTexture);

	// Gate right front corner 2
	GameObject* gateRightFront2 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.15, 1.5, 2.0)), 0.0f, btVector3(31.25f, 2.0f, -37.25f));
	gateRightFront2->SetScale(glm::vec3(0.01, 0.020, 0.01));
	gateRightFront2->AddRotation(glm::vec3(0, 1, 0), 90);
	gateRightFront2->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateRightFront2);
	cell3GameObjects.push_back(gateRightFront2);
	gateRightFront2->ChangeTexture(rustTexture);

	// Pillar right top
	GameObject* pillarRightFront = new GameObject(Narrow_Pillar, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 0.5)), 0.0f, btVector3(31.5f, 0.0f, -35.0f));
	pillarRightFront->SetScale(glm::vec3(0.004, 0.005, 0.007));
	pillarRightFront->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarRightFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarRightFront);
	cell3GameObjects.push_back(pillarRightFront);
	pillarRightFront->SetShouldMove(true);
	pillarRightFront->SetMovement(btVector3(-0.5, 0.25, 0.0));

	// Pedestal right front
	GameObject* pedestalRightFront = new GameObject(techPedestal, GameObject::target, "pedestalTech3", dullMaterial, new btBoxShape(btVector3(1.8, 0.25, 1.8)), 0.0f, btVector3(33.25f, 0.0f, -37.5f));
	pedestalRightFront->SetScale(glm::vec3(0.15, 0.1, 0.15));
	pedestalRightFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pedestalRightFront);
	cell3GameObjects.push_back(pedestalRightFront);
	pedestalRightFront->ChangeTexture(squareTechTexture3);

	// BACK LEFT CORNER

	// Gate left back corner 1
	GameObject* gateLeftBack1 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(2.0, 1.5, 0.15)), 0.0f, btVector3(17.0f, 2.0f, -14.25f));
	gateLeftBack1->SetScale(glm::vec3(0.0075, 0.020, 0.01));
	gateLeftBack1->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateLeftBack1);
	cell3GameObjects.push_back(gateLeftBack1);
	gateLeftBack1->ChangeTexture(rustTexture);

	// Gate left back corner 2
	GameObject* gateLeftBack2 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.15, 1.5, 2.0)), 0.0f, btVector3(19.0f, 2.0f, -12.0f));
	gateLeftBack2->SetScale(glm::vec3(0.01, 0.020, 0.01));
	gateLeftBack2->AddRotation(glm::vec3(0, 1, 0), 90);
	gateLeftBack2->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateLeftBack2);
	cell3GameObjects.push_back(gateLeftBack2);
	gateLeftBack2->ChangeTexture(rustTexture);

	// Pillar left back
	GameObject* pillarLeftBack = new GameObject(Narrow_Pillar, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 0.5)), 0.0f, btVector3(19.0f, 0.0f, -14.0f));
	pillarLeftBack->SetScale(glm::vec3(0.004, 0.005, 0.007));
	pillarLeftBack->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarLeftBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarLeftBack);
	cell3GameObjects.push_back(pillarLeftBack);
	pillarLeftBack->SetShouldMove(true);
	pillarLeftBack->SetMovement(btVector3(-0.5, 0.25, 0.0));

	// Pedestal left back
	GameObject* pedestalLeftBack = new GameObject(techPedestal, GameObject::target, "pedestalTech4", dullMaterial, new btBoxShape(btVector3(1.8, 0.25, 1.8)), 0.0f, btVector3(33.25f, 0.0f, -12.25f));
	pedestalLeftBack->SetScale(glm::vec3(0.15, 0.1, 0.15));
	pedestalLeftBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pedestalLeftBack);
	cell3GameObjects.push_back(pedestalLeftBack);
	pedestalLeftBack->ChangeTexture(squareTechTexture4);

	// BACK RIGHT CORNER

		// Gate right back corner 1
	GameObject* gateRightBack1 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(2.0, 1.5, 0.15)), 0.0f, btVector3(33.5f, 2.0f, -14.25f));
	gateRightBack1->SetScale(glm::vec3(0.0075, 0.020, 0.01));
	gateRightBack1->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateRightBack1);
	cell3GameObjects.push_back(gateRightBack1);
	gateRightBack1->ChangeTexture(rustTexture);

	// Gate right back corner 2
	GameObject* gateRightBack2 = new GameObject(rustyGate, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.15, 1.5, 2.0)), 0.0f, btVector3(31.25f, 2.0f, -12.0f));
	gateRightBack2->SetScale(glm::vec3(0.01, 0.020, 0.01));
	gateRightBack2->AddRotation(glm::vec3(0, 1, 0), 90);
	gateRightBack2->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(gateRightBack2);
	cell3GameObjects.push_back(gateRightBack2);
	gateRightBack2->ChangeTexture(rustTexture);

	// Pillar right back
	GameObject* pillarRightBack = new GameObject(Narrow_Pillar, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 0.5)), 0.0f, btVector3(31.5f, 0.0f, -14.0f));
	pillarRightBack->SetScale(glm::vec3(0.004, 0.005, 0.007));
	pillarRightBack->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarRightBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarRightBack);
	cell3GameObjects.push_back(pillarRightBack);
	pillarRightBack->SetShouldMove(true);
	pillarRightBack->SetMovement(btVector3(-0.5, 0.25, 0.0));

	// Pedestal right back
	GameObject* pedestalRightBack = new GameObject(techPedestal, GameObject::target, "pedestalTech1", dullMaterial, new btBoxShape(btVector3(1.8, 0.25, 1.8)), 0.0f, btVector3(17.25f, 0.0f, -12.25f));
	pedestalRightBack->SetScale(glm::vec3(0.15, 0.1, 0.15));
	pedestalRightBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pedestalRightBack);
	cell3GameObjects.push_back(pedestalRightBack);
	pedestalRightBack->ChangeTexture(squareTechTexture1);

	// Windows front
	GameObject* windowsFront = new GameObject(Windows, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(15.0, 5.0, 0.5)), 0.0f, btVector3(22.5f, 0.0f, -40.0f));
	windowsFront->SetScale(glm::vec3(0.005, 0.005, 0.00675));
	windowsFront->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(windowsFront);
	cell3GameObjects.push_back(windowsFront);

	// Windows front right pillar
	GameObject* pillarFrontRight = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(28.5f, 0.0f, -40.0f));
	pillarFrontRight->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarFrontRight->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarFrontRight);
	cell3GameObjects.push_back(pillarFrontRight);
	pillarFrontRight->SetShouldMove(true);
	pillarFrontRight->SetMovement(btVector3(-1.25, 1.25, 0.0));

	// Windows front left pillar
	GameObject* pillarFrontLeft = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(21.5f, 0.0f, -40.0f));
	pillarFrontLeft->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarFrontLeft->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarFrontLeft);
	cell3GameObjects.push_back(pillarFrontLeft);
	pillarFrontLeft->SetShouldMove(true);
	pillarFrontLeft->SetMovement(btVector3(-1.25, 1.25, 0.0));

	// Brick Wall front right
	GameObject* brickWallFrontRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(29.25f, 0.0f, -40.0f));
	brickWallFrontRight->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontRight->SetUseMaterial(true);
	nonPhysicsGameObjects.push_back(brickWallFrontRight);
	cell3GameObjects.push_back(brickWallFrontRight);

	// Brick Wall front left
	GameObject* brickWallFrontLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(15.0f, 0.0f, -40.0f));
	brickWallFrontLeft->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFrontLeft->SetUseMaterial(true);
	nonPhysicsGameObjects.push_back(brickWallFrontLeft);
	cell3GameObjects.push_back(brickWallFrontLeft);

	// Windows back
	GameObject* windowsBack = new GameObject(Windows, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(22.5f, 0.0f, -10.0f));
	windowsBack->SetScale(glm::vec3(0.005, 0.005, 0.00675));
	windowsBack->AddRotation(glm::vec3(1, 0, 0), -90);
	windowsBack->SetUseMaterial(true);
	nonPhysicsGameObjects.push_back(windowsBack);
	cell3GameObjects.push_back(windowsBack);

	// Windows back right pillar
	GameObject* pillarBackRight = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(28.5f, 0.0f, -10.0f));
	pillarBackRight->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarBackRight->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarBackRight);
	cell3GameObjects.push_back(pillarBackRight);
	pillarBackRight->SetShouldMove(true);
	pillarBackRight->SetMovement(btVector3(-1.25, 1.25, 0.0));

	// Windows back left pillar
	GameObject* pillarBackLeft = new GameObject(Pillar_Standalone, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.25, 5.0, 1.25)), 0.0f, btVector3(21.5f, 0.0f, -10.0f));
	pillarBackLeft->SetScale(glm::vec3(0.005, 0.005, 0.0055));
	pillarBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	pillarBackLeft->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(pillarBackLeft);
	cell3GameObjects.push_back(pillarBackLeft);
	pillarBackLeft->SetShouldMove(true);
	pillarBackLeft->SetMovement(btVector3(-1.25, 1.25, 0.0));

	// Brick Wall back right
	GameObject* brickWallBackRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(15.0, 5.0, 0.5)), 0.0f, btVector3(29.25f, 0.0f, -10.0f));
	brickWallBackRight->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallBackRight->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallBackRight);
	cell3GameObjects.push_back(brickWallBackRight);

	// Brick Wall back left
	GameObject* brickWallBackLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(15.0f, 0.0f, -10.0f));
	brickWallBackLeft->SetScale(glm::vec3(0.006, 0.008, 0.00675));
	brickWallBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallBackLeft->SetUseMaterial(true);
	nonPhysicsGameObjects.push_back(brickWallBackLeft);
	cell3GameObjects.push_back(brickWallBackLeft);

	// Brick Wall right back
	GameObject* brickWallRightBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 13.5)), 0.0f, btVector3(35.0f, 0.0f, -10.0f));
	brickWallRightBack->SetScale(glm::vec3(0.01415, 0.008, 0.00675));
	brickWallRightBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightBack->AddRotation(glm::vec3(0, 0, 1), 90);
	brickWallRightBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallRightBack);
	cell4GameObjects.push_back(roof);

	// Brick Wall right front
	GameObject* brickWallRightFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 13.0)), 0.0f, btVector3(35.5f, 0.0f, -39.5f));
	brickWallRightFront->SetScale(glm::vec3(0.014, 0.008, 0.00675));
	brickWallRightFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRightFront->AddRotation(glm::vec3(0, 0, 1), 270);
	brickWallRightFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallRightFront);
	cell4GameObjects.push_back(roof);

	// Tech box 1
	GameObject* techBox1 = new GameObject(cube, GameObject::interactive, "techBox1", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, btVector3(25.0f, 0.5f, -30.0f));
	techBox1->SetScale(glm::vec3(0.5, 0.5, 0.5));
	techBox1->SetInteractable(true);
	physicsWorld->AddObjectToPhysicsWorld(techBox1);
	cell3GameObjects.push_back(techBox1);
	techBox1->ChangeTexture(squareTechTexture1);

	// Tech box 2
	GameObject* techBox2 = new GameObject(cube, GameObject::interactive, "techBox2", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, btVector3(25.0f, 0.5f, -20.0f));
	techBox2->SetScale(glm::vec3(0.5, 0.5, 0.5));
	techBox2->SetInteractable(true);
	physicsWorld->AddObjectToPhysicsWorld(techBox2);
	cell3GameObjects.push_back(techBox2);
	techBox2->ChangeTexture(squareTechTexture2);

	// Tech box 3
	GameObject* techBox3 = new GameObject(cube, GameObject::interactive, "techBox3", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, btVector3(20.0f, 0.5f, -25.0f));
	techBox3->SetScale(glm::vec3(0.5, 0.5, 0.5));
	techBox3->SetInteractable(true);
	physicsWorld->AddObjectToPhysicsWorld(techBox3);
	cell3GameObjects.push_back(techBox3);
	techBox3->ChangeTexture(squareTechTexture3);

	// Tech box 4
	GameObject* techBox4 = new GameObject(cube, GameObject::interactive, "techBox4", shinyMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 1.0f, btVector3(30.0f, 0.5f, -25.0f));
	techBox4->SetScale(glm::vec3(0.5, 0.5, 0.5));
	techBox4->SetInteractable(true);
	physicsWorld->AddObjectToPhysicsWorld(techBox4);
	cell3GameObjects.push_back(techBox4);
	techBox4->ChangeTexture(squareTechTexture4);
}

void SceneManager::BuildCell4()
{
	// FLOOR
	GameObject* floor = new GameObject(new btBoxShape(btVector3(7, 0, 10)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("FloorCell4"), floorSquares, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(42.0f, 0.0f, -25.0f));
	physicsWorld->AddObjectToPhysicsWorld(floor);
	cell4GameObjects.push_back(floor);

	// Roof
	GameObject* roof = new GameObject(new btBoxShape(btVector3(5, 0, 10)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("RoofCell4"), brick, shinyMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(40.0f, 5.0f, -25.0f));
	roof->AddRotation(glm::vec3(1, 0, 0), -180);
	physicsWorld->AddObjectToPhysicsWorld(roof);
	cell4GameObjects.push_back(roof);

	// Cornice right
	GameObject* corniceRight = new GameObject(Cornice, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 1.0, 20.0)), 0.0f, btVector3(48.5f, 0.0f, -15.0f));
	corniceRight->SetScale(glm::vec3(0.021, 0.008, 0.00675));
	corniceRight->AddRotation(glm::vec3(1, 0, 0), -90);
	corniceRight->AddRotation(glm::vec3(0, 0, 1), 90);
	corniceRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(corniceRight);
	cell4GameObjects.push_back(corniceRight);

	// Cathedral Window front
	GameObject* windowFront = new GameObject(Cathedral_Window, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(39.0f, 0.0f, -35.0f));
	windowFront->SetScale(glm::vec3(0.0105, 0.005, 0.005));
	windowFront->AddRotation(glm::vec3(1, 0, 0), -90);
	windowFront->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(windowFront);
	cell4GameObjects.push_back(windowFront);

	// Wide pillar front left
	GameObject* widePillarFrontLeft = new GameObject(Wide_Pillar_No_Door, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(35.5f, 0.0f, -35.3f));
	widePillarFrontLeft->SetScale(glm::vec3(0.008, 0.005, 0.005));
	widePillarFrontLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	widePillarFrontLeft->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(widePillarFrontLeft);
	cell4GameObjects.push_back(widePillarFrontLeft);

	// Wide pillar front right
	GameObject* widePillarFrontRight = new GameObject(Wide_Pillar_No_Door, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(10.0, 5.0, 0.5)), 0.0f, btVector3(45.0f, 0.0f, -35.3f));
	widePillarFrontRight->SetScale(glm::vec3(0.008, 0.005, 0.005));
	widePillarFrontRight->AddRotation(glm::vec3(1, 0, 0), -90);
	widePillarFrontRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(widePillarFrontRight);
	cell4GameObjects.push_back(widePillarFrontRight);

	// Cathedral Window back
	GameObject* windowBack = new GameObject(Cathedral_Window, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(45.1f, 0.0f, -15.0f));
	windowBack->SetScale(glm::vec3(0.0105, 0.005, 0.005));
	windowBack->AddRotation(glm::vec3(1, 0, 0), -90);
	windowBack->AddRotation(glm::vec3(0, 0, 1), 180);
	windowBack->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(windowBack);
	cell4GameObjects.push_back(windowBack);

	// Wide pillar back left
	GameObject* widePillarBackLeft = new GameObject(Wide_Pillar_No_Door, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 0.5, 0.5)), 0.0f, btVector3(35.5f, 0.0f, -15.4f));
	widePillarBackLeft->SetScale(glm::vec3(0.008, 0.005, 0.005));
	widePillarBackLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	widePillarBackLeft->SetUseMaterial(false);
	nonPhysicsGameObjects.push_back(widePillarBackLeft);
	cell4GameObjects.push_back(widePillarBackLeft);

	// Wide pillar back right
	GameObject* widePillarBackRight = new GameObject(Wide_Pillar_No_Door, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(10.0, 5.0, 0.5)), 0.0f, btVector3(45.0f, 0.0f, -15.4f));
	widePillarBackRight->SetScale(glm::vec3(0.008, 0.005, 0.005));
	widePillarBackRight->AddRotation(glm::vec3(1, 0, 0), -90);
	widePillarBackRight->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(widePillarBackRight);
	cell4GameObjects.push_back(widePillarBackRight);

	// Chandelier front
	GameObject* chandelierFront = new GameObject(chandelier, GameObject::env, "", shinyMaterial, new btBoxShape(btVector3(0.75, 0.75, 0.75)), 0.0f, btVector3(42.0f, 3.4f, -32.5f));
	chandelierFront->SetScale(glm::vec3(0.2, 0.2, 0.2));
	chandelierFront->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(chandelierFront);
	cell4GameObjects.push_back(chandelierFront);
	chandelierFront->SetShouldMove(true);
	chandelierFront->SetMovement(btVector3(0, -1, 0.75));

	// Chandelier back
	GameObject* chandelierBack = new GameObject(chandelier, GameObject::env, "", shinyMaterial, new btBoxShape(btVector3(0.75, 0.75, 0.75)), 0.0f, btVector3(42.0f, 3.4f, -17.0f));
	chandelierBack->SetScale(glm::vec3(0.2, 0.2, 0.2));
	chandelierBack->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(chandelierBack);
	cell4GameObjects.push_back(chandelierBack);
	chandelierBack->SetShouldMove(true);
	chandelierBack->SetMovement(btVector3(0, -1, 0.75));

	// Dispenser front
	GameObject* dispenserFront = new GameObject(dispenserExport, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.0, 1.5, 1.0)), 0.0f, btVector3(39.0f, 6.5f, -30.0f));
	dispenserFront->SetScale(glm::vec3(2.5, 2.0, 2.5));
	dispenserFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(dispenserFront);
	cell4GameObjects.push_back(dispenserFront);
	dispenserFront->ChangeTexture(rustTexture);

	// Dispenser back
	GameObject* dispenserBack = new GameObject(dispenserExport, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(1.0, 1.5, 1.0)), 0.0f, btVector3(39.0f, 6.5f, -20.0f));
	dispenserBack->SetScale(glm::vec3(2.5, 2.0, 2.5));
	dispenserBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(dispenserBack);
	cell4GameObjects.push_back(dispenserBack);

	dispenserBack->ChangeTexture(rustTexture);

	// Button
	GameObject* button = new GameObject(Switch_round_button, GameObject::env, "button", dullMaterial, new btBoxShape(btVector3(0.35, 0.35, 0.35)), 0.0f, btVector3(35.5f, 2.0f, -23.0f));
	button->SetScale(glm::vec3(10.0, 10.0, 10.0));
	button->AddRotation(glm::vec3(1, 0, 0), 90);
	button->AddRotation(glm::vec3(0, 0, 1), 90);
	button->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(button);
	cell4GameObjects.push_back(button);

	// SCREEN 3
	GameObject* screen = new GameObject(new btBoxShape(btVector3(1.5, 0, 1.5)), 0.0f, Shapes::squareStretch, GameObject::env, std::string("Screen3"), screen3, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(35.75f, 2.0f, -20.0f));
	screen->AddRotation(glm::vec3(1, 0, 0), 90);
	screen->AddRotation(glm::vec3(0, 0, 1), -90);
	nonPhysicsGameObjects.push_back(screen);
	cell4GameObjects.push_back(screen);

	GameObject* destroyZone = new GameObject(new btBoxShape(btVector3(30.0, 0.25, 30.0)), 0.0f, "destroy", btVector3(80, -5, -25));
	physicsWorld->AddObjectToPhysicsWorld(destroyZone);
	cell4GameObjects.push_back(destroyZone);

	GameObject* destroyZone2 = new GameObject(new btBoxShape(btVector3(0.25, 50.0, 50.0)), 0.0f, "destroy2", btVector3(60, -5, -25));
	physicsWorld->AddObjectToPhysicsWorld(destroyZone2);
	cell4GameObjects.push_back(destroyZone2);

	// Timer
	timer = new CountDownTimer(180, btVector3(34.60, 2, -32), dullMaterial);
}

void SceneManager::BuildEndCell()
{
	// FLOOR
	GameObject* floor = new GameObject(new btBoxShape(btVector3(5, 0, 5)), 0.0f, Shapes::squareRepeat, GameObject::env, std::string("FloorCellEnd"), floorSquares, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(-25.0f, 0.0f, -25.0f));
	physicsWorld->AddObjectToPhysicsWorld(floor);

	// SCREEN
	GameObject* screen = new GameObject(new btBoxShape(btVector3(5.0, 0.25, 4.0)), 0.0f, Shapes::squareStretch, GameObject::env, std::string("Screen2"), screen4, dullMaterial, btVector3(1.0f, 1.0f, 1.0f), btVector3(-25.0f, 0.0f, -29.90f));
	screen->AddRotation(glm::vec3(1, 0, 0), 90);
	nonPhysicsGameObjects.push_back(screen);

	numberDisplay = new NumberDisplay(GameManager::GetInstance()->GetScoreManager()->GetScore(), btVector3(-25.0f, 1.0f, -30.60f), dullMaterial);

	// Brick Wall front
	GameObject* brickWallFront = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(10.0, 5.0, 0.5)), 0.0f, btVector3(-30.0f, 0.0f, -30.0f));
	brickWallFront->SetScale(glm::vec3(0.012, 0.005, 0.00675));
	brickWallFront->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallFront->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallFront);

	// Brick Wall back
	GameObject* brickWallBack = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(10.0, 5.0, 0.5)), 0.0f, btVector3(-30.0f, 0.0f, -20.0f));
	brickWallBack->SetScale(glm::vec3(0.012, 0.005, 0.00675));
	brickWallBack->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallBack->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallBack);

	// Brick Wall left
	GameObject* brickWallLeft = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 10.0)), 0.0f, btVector3(-30.0f, 0.0f, -30.0f));
	brickWallLeft->SetScale(glm::vec3(0.012, 0.005, 0.00675));
	brickWallLeft->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallLeft->AddRotation(glm::vec3(0, 0, 1), -90);
	brickWallLeft->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallLeft);

	// Brick Wall right
	GameObject* brickWallRight = new GameObject(Brick_Wall, GameObject::env, "", dullMaterial, new btBoxShape(btVector3(0.5, 5.0, 10.0)), 0.0f, btVector3(-20.0f, 0.0f, -30.0f));
	brickWallRight->SetScale(glm::vec3(0.012, 0.005, 0.00675));
	brickWallRight->AddRotation(glm::vec3(1, 0, 0), -90);
	brickWallRight->AddRotation(glm::vec3(0, 0, 1), -90);
	brickWallRight->SetUseMaterial(true);
	physicsWorld->AddObjectToPhysicsWorld(brickWallRight);
}


void SceneManager::DestroyNonPhysicsGameObject(GameObject* gameObject)
{
	for (GameObjects::iterator iter = nonPhysicsGameObjects.begin(); iter != nonPhysicsGameObjects.end(); ++iter)
	{
		if ((*iter) == gameObject)
		{
			nonPhysicsGameObjects.erase(iter);

			delete gameObject;

			return;
		}
	}
}

void SceneManager::DeleteCell1()
{
	for (GameObjects::iterator iter = cell1GameObjects.begin(); iter != cell1GameObjects.end(); ++iter)
	{
		GameObject* object = *iter;

		physicsWorld->DestroyGameObject(object->GetRigidBody());
		DestroyNonPhysicsGameObject(object);
	}

	cell1GameObjects.clear();

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell1", dullMaterial, new btBoxShape(btVector3(1.4, 2.0, 0.5)), 0.0f, btVector3(-0.075f, 2.0f, -9.75f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(gate);
	cell2GameObjects.push_back(gate);
	gate->ChangeTexture(rustTexture);

	cell1Deleted = true;
}

void SceneManager::DeleteCell2()
{
	for (GameObjects::iterator iter = cell2GameObjects.begin(); iter != cell2GameObjects.end(); ++iter)
	{
		GameObject* object = *iter;

		physicsWorld->DestroyGameObject(object->GetRigidBody());
		DestroyNonPhysicsGameObject(object);
	}

	cell2GameObjects.clear();

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell2", dullMaterial, new btBoxShape(btVector3(0.5, 2.0, 1.4)), 0.0f, btVector3(15.25f, 2.0f, -24.85f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->AddRotation(glm::vec3(0, 1, 0), 90);
	gate->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(gate);
	cell3GameObjects.push_back(gate);
	gate->ChangeTexture(rustTexture);

	cell2Deleted = true;
}

void SceneManager::DeleteCell3()
{
	for (GameObjects::iterator iter = cell3GameObjects.begin(); iter != cell3GameObjects.end(); ++iter)
	{
		GameObject* object = *iter;

		physicsWorld->DestroyGameObject(object->GetRigidBody());
		DestroyNonPhysicsGameObject(object);
	}

	cell3GameObjects.clear();

	// Gate
	GameObject* gate = new GameObject(rustyGate, GameObject::env, "gateCell3", dullMaterial, new btBoxShape(btVector3(0.5, 2.0, 1.4)), 0.0f, btVector3(35.25f, 2.0f, -24.85f));
	gate->SetScale(glm::vec3(0.0055, 0.025, 0.01));
	gate->AddRotation(glm::vec3(0, 1, 0), 90);
	gate->SetUseMaterial(false);
	physicsWorld->AddObjectToPhysicsWorld(gate);
	gate->ChangeTexture(rustTexture);

	cell3Deleted = true;
}

void SceneManager::DeleteCell4()
{
	for (GameObjects::iterator iter = cell4GameObjects.begin(); iter != cell4GameObjects.end(); ++iter)
	{
		GameObject* object = *iter;

		physicsWorld->DestroyGameObject(object->GetRigidBody());
		DestroyNonPhysicsGameObject(object);
	}

	cell4GameObjects.clear();
}


void SceneManager::RenderGameObjects(GLuint& uniformModel, GLuint& uniformSpecularIntensity, GLuint& uniformShininessLocation)
{
	int nonPhy = 0, phy = 0;

	for (GameObjects::iterator i = nonPhysicsGameObjects.begin(); i != nonPhysicsGameObjects.end(); ++i)
	{
		GameObject* obj = *i;

		obj->RenderGameObject(uniformModel, uniformSpecularIntensity, uniformShininessLocation);

		nonPhy++;
	}

	for (GameObjects::iterator i = physicsWorld->gameObjects.begin(); i != physicsWorld->gameObjects.end(); ++i)
	{
		GameObject* obj = *i;

		obj->RenderGameObject(uniformModel, uniformSpecularIntensity, uniformShininessLocation);

		phy++;
	}

	if (physicsWorld->GetActiveCell() == PhysicsLayer::cell4 && timer)
		timer->RenderTimer(uniformModel, uniformSpecularIntensity, uniformShininessLocation);
	else if (physicsWorld->GetActiveCell() == PhysicsLayer::cellEnd)
		numberDisplay->RenderNumber(uniformModel, uniformSpecularIntensity, uniformShininessLocation);
}

void SceneManager::CreateCustomBox(std::string name, GameObject::ObjectTypes objType, const btVector3& scale, const btVector3& color, const btVector3& randomPos)
{
	GameObject* box = new GameObject(new btBoxShape(scale), 1.0f, Shapes::cube, objType, name, sandWhite, shinyMaterial, color, randomPos);
	physicsWorld->AddObjectToPhysicsWorld(box);
	box->SetInteractable(true);
}

void SceneManager::CreateRandomBox()
{
	std::array<int, 3> random_numbers = { -20, -25, -30 };

	std::random_device random_device;
	std::mt19937 engine(random_device());
	std::uniform_int_distribution<int> distribution(0, random_numbers.size() - 1);
	std::uniform_int_distribution<int> distribution2(0, 7);

	const int random_number_pos = random_numbers[distribution(engine)];
	const int random_number_box = distribution2(engine);

	switch (random_number_box)
	{
	case 0:
		CreateCustomBox(std::string("rB"), GameObject::target, btVector3(1, 1, 1), btVector3(1, 0, 0), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 1:
		CreateCustomBox(std::string("gB"), GameObject::target, btVector3(1, 1, 1), btVector3(0, 1, 0), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 2:
		CreateCustomBox(std::string("bB"), GameObject::target, btVector3(1, 1, 1), btVector3(0, 0, 1), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 3:
		CreateCustomBox(std::string("yB"), GameObject::target, btVector3(1, 1, 1), btVector3(1, 1, 0), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 4:
		CreateCustomBox(std::string("pB"), GameObject::target, btVector3(1, 1, 1), btVector3(1, 0, 1), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 5:
		CreateCustomBox(std::string("cB"), GameObject::target, btVector3(1, 1, 1), btVector3(0, 1, 1), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 6:
		CreateCustomBox(std::string("oB"), GameObject::target, btVector3(1, 1, 1), btVector3(1, 0.5, 0), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	case 7:
		CreateCustomBox(std::string("grB"), GameObject::target, btVector3(1, 1, 1), btVector3(0.5, 0.5, 0.5), btVector3(55.0f, 10.0f, random_number_pos));
		break;
	}
}

void SceneManager::CreateRandomBoxAtPos(const btVector3& pos)
{
	std::random_device random_device;
	std::mt19937 engine(random_device());
	std::uniform_int_distribution<int> distribution2(0, 7);

	const int random_number_box = distribution2(engine);

	switch (random_number_box)
	{
	case 0:
		CreateCustomBox(std::string("rBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(1, 0, 0), pos);
		break;
	case 1:
		CreateCustomBox(std::string("gBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(0, 1, 0), pos);
		break;
	case 2:
		CreateCustomBox(std::string("bBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(0, 0, 1), pos);
		break;
	case 3:
		CreateCustomBox(std::string("yBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(1, 1, 0), pos);
		break;
	case 4:
		CreateCustomBox(std::string("pBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(1, 0, 1), pos);
		break;
	case 5:
		CreateCustomBox(std::string("cBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(0, 1, 1), pos);
		break;
	case 6:
		CreateCustomBox(std::string("oBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(1, 0.5, 0), pos);
		break;
	case 7:
		CreateCustomBox(std::string("grBp"), GameObject::interactive, btVector3(0.5, 0.5, 0.5), btVector3(0.5, 0.5, 0.5), pos);
		break;
	}
}

SceneManager::~SceneManager()
{
	
}
