#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h" 
#include "Shader.h"
#include "ShaderText.h"
#include "Camera.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "GameManager.h"
#include "ScreenManager.h"
#include "SceneManager.h"

#include "FileManager.h"

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininessLocation = 0;

Window mainWindow;
Shader mainShader;
Shader directionalShadowShader;
ShaderText textShader;

Camera* camera;

ScreenManager* screenManager;
SceneManager* scene_manager;

PhysicsLayer* physicsWorldPointer;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool flashLightOn;

bool buttonPressed = false;
bool cell4InitialStart = true;
bool processedMistakeSkipFall = false;
bool processedMistakeReduceTime = false;

bool gameOver = false;

system_clock::time_point start, start2, over;

void CreateShaders()
{
	mainShader = Shader();
	mainShader.CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");

	directionalShadowShader = Shader();
	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");

	textShader = ShaderText();
	textShader.CreateFromFiles("Shaders/text.vert", "Shaders/text.frag");
}

void CreateLights()
{
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.1f, 0.5, // 0.2, 0.3
		0.0f, -50.0f, -30.0f,
		2048, 2048);

	// Cell 1 light 1
	pointLights[0] = PointLight(1.0f, 1.0f, 0.8f,
		0.1f, 1.0f, // 0.1, 1.0
		6.0f, 3.0f, 7.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 1 light 2
	pointLights[1] = PointLight(1.0f, 1.0f, 0.8f,
		0.1f, 1.0f, // 0.1 1.0
		-6.0f, 3.0f, 7.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 2 light 1
	pointLights[2] = PointLight(1.0f, 0.0f, 0.0f,
		0.1f, 1.0f, // 0.1, 1.0
		-9.0f, 2.0f, -34.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 2 light 2
	pointLights[3] = PointLight(0.0f, 1.0f, 0.0f,
		0.1f, 1.0f, // 0.1 1.0
		-9.0f, 2.0f, -19.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 2 light 3
	pointLights[4] = PointLight(0.0f, 0.0f, 1.0f,
		0.1f, 1.0f, // 0.1, 1.0
		9.0f, 2.0f, -34.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 2 light 4
	pointLights[5] = PointLight(1.0f, 1.0f, 0.0f,
		0.1f, 1.0f, // 0.1 1.0
		9.0f, 2.0f, -19.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 4 light 1
	pointLights[6] = PointLight(1.0f, 1.0f, 0.8f,
		0.1f, 1.0f, // 0.1, 1.0
		42.0f, 3.0f, -32.5f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	// Cell 4 light 2
	pointLights[7] = PointLight(1.0f, 1.0f, 0.8f,
		0.1f, 1.0f, // 0.1 1.0
		42.0f, 3.0f, -17.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;


	// Flashlight
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;
}

void FlashlightDisplay()
{
	if (flashLightOn)
	{
		glm::vec3 lowerLight = camera->GetCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera->GetCameraDirection());
	}
	else
	{
		spotLights[0].SetFlash(glm::vec3(1000, 1000, 100), glm::vec3(0, 0, 0));
	}
}

void RenderScene()
{
	scene_manager->RenderGameObjects(uniformModel, uniformSpecularIntensity, uniformShininessLocation);

	// Debug drawing 
	//brickTexture.UseTexture();
	//shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininessLocation);
	//physicsWorldPointer->GetDebugDrawer()->passedUniformModel = uniformModel;
	//physicsWorldPointer->GetDynamicWorld()->debugDrawWorld();

	//btVector3 pos = camera->GetBtV3CameraPosition();
	//pos.setY(pos.getY() - 1);

	//physicsWorldPointer->GetDebugDrawer()->drawLine(pos, physicsWorldPointer->GetDebugRayTo(), btVector3(1, 0, 0));
	//physicsWorldPointer->GetDebugDrawer()->drawLine(pos, physicsWorldPointer->GetDebugRayTo2(), btVector3(1, 0, 0));
	//physicsWorldPointer->GetDebugDrawer()->drawLine(pos, physicsWorldPointer->GetDebugRayTo3(), btVector3(1, 0, 0));
	//physicsWorldPointer->GetDebugDrawer()->drawLine(pos, physicsWorldPointer->GetDebugRayTo4(), btVector3(1, 0, 0));
}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(light->CalculateLightTransform());

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 ViewMatrix)
{
	mainShader.UseShader();

	uniformModel = mainShader.GetModelLocation();
	uniformProjection = mainShader.GetProjectionLocation();
	uniformView = mainShader.GetViewLocation();
	uniformEyePosition = mainShader.GetEyePositionLocation();
	uniformSpecularIntensity = mainShader.GetSpecularIntensityLocation();
	uniformShininessLocation = mainShader.GetShininessLocation();

	glViewport(0, 0, 1366, 768);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniform3f(uniformEyePosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

	mainShader.SetDirectionalLight(&mainLight);
	mainShader.SetPointLights(pointLights, pointLightCount);
	mainShader.SetSpotLights(spotLights, spotLightCount);
	mainShader.SetDirectionalLightTransform(mainLight.CalculateLightTransform());

	mainLight.GetShadowMap()->Read(GL_TEXTURE1);
	mainShader.SetTexture(0);
	mainShader.SetDirectionalShadowMap(1);

	FlashlightDisplay();

	if (physicsWorldPointer->GetPickedBody())
	{
		btGeneric6DofConstraint* pickCon = static_cast<btGeneric6DofConstraint*>(physicsWorldPointer->GetPickConstraint());

		if (!pickCon)
			return;

		// Use another picking ray to get the target direction
		btVector3 dir = camera->GetBtV3CameraDirection() * 1000 - camera->GetBtV3CameraPosition();
		dir.normalize();

		// Use the same distance as when we originally picked the object
		dir *= physicsWorldPointer->GetOldPickingDistance();
		btVector3 newPivot = camera->GetBtV3CameraPosition() + dir;

		// Set the position of the constraint
		pickCon->getFrameOffsetA().setOrigin(newPivot);
	}

	RenderScene();
}

void MouseFunction(bool* mouseButtons)
{
	// left mouse button pressed
	if (mouseButtons[0])
	{
		if (GameManager::GetInstance()->GetActiveState() == GameManager::inGame)
		{
			if (!physicsWorldPointer->IsHoldingObject())
			{
				if (physicsWorldPointer->CreatePickingConstraint(camera))
					physicsWorldPointer->SetHolding(true);
				else if (physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell4 && !buttonPressed)
				{
					RayResult output;

					if (physicsWorldPointer->Raycast(camera->GetBtV3CameraPosition(), camera->GetBtV3CameraDirection(), output, 1000))
					{

						if (physicsWorldPointer->FindGameObject(output.body)->GetName() == "button")
						{
							buttonPressed = true;
							SoundManager::GetInstance()->PlayCorrectSound();
						}
					}
				}
			}
			else
				physicsWorldPointer->RemovePickingConstraint();
		}
		else if (GameManager::GetInstance()->GetActiveState() == GameManager::start)
		{
			screenManager->CheckMainMenuInputEvent();
		}
		else if (GameManager::GetInstance()->GetActiveState() == GameManager::paused)
		{
			screenManager->CheckPauseMenuInputEvent();
		}
	}

	// right mouse button pressed
	if (mouseButtons[1])
	{
		if (physicsWorldPointer)
		{
			if (physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell3 || physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell4)
			{
				physicsWorldPointer->ShootPickedObject(camera->GetBtV3CameraDirection(), *physicsWorldPointer->GetPickedBody());
			}
		}
	}
}

void KeyControlFunction(bool* keys)
{
	if (GameManager::GetInstance()->GetActiveState() == GameManager::start)
	{
		for (int i = 65; i <= 122; i++) // valid keys for name
		{
			if (keys[i])
			{
				screenManager->AddCharacterToName(i);
			}
		}
		if (keys[GLFW_KEY_BACKSPACE])
			screenManager->BackspaceName();
	}

	if (keys[GLFW_KEY_V])
	{
		if (physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell3 || physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell4)
		{
			flashLightOn = !flashLightOn;
		}
	}
	else if (keys[GLFW_KEY_ESCAPE])
	{
		if (GameManager::GetInstance()->GetActiveState() == GameManager::inGame)
		{
			GameManager::GetInstance()->SetActiveState(GameManager::paused);
		}
		else if (GameManager::GetInstance()->GetActiveState() == GameManager::paused)
		{
			GameManager::GetInstance()->SetActiveState(GameManager::inGame);
		}
	}
}

void Input::InputProcess(bool mouse, bool keyboard)
{
	if (mouse)
		MouseFunction(mainWindow.GetMouseButtons());
	if (keyboard)
		KeyControlFunction(mainWindow.GetKeys());
}

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialize();

	camera = new Camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	const glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow.GetBufferWidth()) / mainWindow.GetBufferHeight(), 0.1f, 100.0f);
	const glm::mat4 projectionText = glm::ortho(0.0f, static_cast<GLfloat>(mainWindow.GetBufferWidth()), 0.0f, static_cast<GLfloat>(mainWindow.GetBufferHeight()));

	CreateShaders();

	textShader.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(textShader.GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projectionText));

	CreateLights();

	screenManager = new ScreenManager(&mainWindow);

	//SoundManager::GetInstance()->PlayBackgroundSound();

	// Loop
	while (!mainWindow.ShouldClose())
	{
		// Delta time for constant game speed
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		if (GameManager::GetInstance()->GetActiveState() == GameManager::start)
		{
			// Handle user input
			glfwPollEvents();

			glfwSetInputMode(mainWindow.GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			screenManager->DisplayMainMenu(textShader);
		}
		else if (GameManager::GetInstance()->GetActiveState() == GameManager::paused)
		{
			// Handle user input
			glfwPollEvents();

			glfwSetInputMode(mainWindow.GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			screenManager->DisplayPauseMenu(textShader);
		}
		else if (GameManager::GetInstance()->GetActiveState() == GameManager::inGame)
		{
			glfwSetInputMode(mainWindow.GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (screenManager->GetIsRestarted())
			{
				screenManager->SetRestarted(false);
				try
				{
					delete scene_manager;
				}
				catch (...)
				{
				}
				scene_manager = new SceneManager();
				physicsWorldPointer = scene_manager->GetPhysicsWorld();
				physicsWorldPointer->SetActiveCell(PhysicsLayer::cell1);
				scene_manager->BuildCell1();
				scene_manager->BuildCell2();
				gameOver = false;
				flashLightOn = false;
				buttonPressed = false;
				cell4InitialStart = true;
				processedMistakeSkipFall = false;
				processedMistakeReduceTime = false;
				GameManager::GetInstance()->GetScoreManager()->ResetScore();
				GameManager::GetInstance()->ResetMistakeCount();
				screenManager->StopDisplayLoading();
				camera->SetCameraPosition(glm::vec3(0.0f, 2.0f, 4.0f));
			}
			if (!gameOver)
			{
				if (physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell3 && scene_manager->GetCell3Built() == false)
				{
					scene_manager->BuildCell3();
					scene_manager->SetCell3Built(true);
				}
				else if (physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell4 && scene_manager->GetCell4Built() == false)
				{
					scene_manager->BuildCell4();
					scene_manager->SetCell4Built(true);
					start = system_clock::now();
					start2 = system_clock::now();
				}
				else if (buttonPressed)
				{
					if (cell4InitialStart)
					{
						cell4InitialStart = false;
						scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -30.0f));
						scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -20.0f));
					}

					over = system_clock::now();
					const duration<int> timeSpan = duration_cast<duration<int>>(over - start);
					const duration<int> timeSpan2 = duration_cast<duration<int>>(over - start2);

					if (timeSpan.count() >= 2)
					{
						scene_manager->CreateRandomBox();
						start = over;
					}

					if (timeSpan2.count() >= 10)
					{
						if (processedMistakeSkipFall)
						{
							scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -30.0f));
							scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -20.0f));
						}
						else
						{
							if (GameManager::GetInstance()->GetMistakeCount() == 2)
							{
								processedMistakeSkipFall = true;
							}
							else
							{
								scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -30.0f));
								scene_manager->CreateRandomBoxAtPos(btVector3(39.0f, 4.0f, -20.0f));
							}
						}
						start2 = over;
					}

					if (GameManager::GetInstance()->GetMistakeCount() == 4)
					{
						if (!processedMistakeReduceTime)
						{
							scene_manager->GetTimer()->ReduceTime(10);
							processedMistakeReduceTime = true;
						}
					}
					
					scene_manager->GetTimer()->CalculateTime();

					if (scene_manager->GetTimer()->HasEnded())
					{
						physicsWorldPointer->RemovePickingConstraint();
						gameOver = true;
						scene_manager->BuildEndCell();
						scene_manager->DeleteCell4();
						camera->SetCameraPosition(glm::vec3(-25, 2, -25));
						camera->SetCameraPitch(0.0f);
						camera->SetCameraYaw(-90.0f);
						flashLightOn = false;
						physicsWorldPointer->SetActiveCell(PhysicsLayer::cellEnd);

						map<string, int> m = screenManager->GetHighScoreMap();
						map<string, int>::iterator it = m.find(screenManager->GetName());

						if (it == m.end())
						{
							// Not found
							m.insert(std::pair<string, int>(screenManager->GetName(), GameManager::GetInstance()->GetScoreManager()->GetScore()));
						}
						else
						{
							// Found
							if (GameManager::GetInstance()->GetScoreManager()->GetScore() > it->second)
								it->second = GameManager::GetInstance()->GetScoreManager()->GetScore();
						}

						if (!FileManager::WriteMap("highScore.txt", m))
							std::cout << "Error writing to file highScore.txt" << std::endl;

						screenManager->UpdateScore();
					}
				}

				if (scene_manager->GetCell1Deleted() == false && physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell2 && camera->GetBtV3CameraPosition().getZ() < -12)
					scene_manager->DeleteCell1();
				else if (scene_manager->GetCell2Deleted() == false && physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell3 && camera->GetBtV3CameraPosition().getX() > 18)
					scene_manager->DeleteCell2();
				else if (scene_manager->GetCell3Deleted() == false && physicsWorldPointer->GetActiveCell() == PhysicsLayer::cell4 && camera->GetBtV3CameraPosition().getX() >= 39)
					scene_manager->DeleteCell3();
			}

			// Update the scene
			scene_manager->GetPhysicsWorld()->UpdateScene();

			// Handle user input
			glfwPollEvents();

			camera->KeyControl(mainWindow.GetKeys(), deltaTime, scene_manager->GetPhysicsWorld()->CheckPlayerCollision(camera));
			camera->MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

			DirectionalShadowMapPass(&mainLight);
			RenderPass(projection, camera->CalculateViewMatrix());

			glUseProgram(0);
		}
		mainWindow.SwapBuffers();
	}

	return 0;
}