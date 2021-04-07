#pragma once

#include <array>
#include <random>
#include "GameObject.h"
#include "PhysicsLayer.h"
#include "CountdownTimer.h"
#include "NumberDisplay.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void BuildCell1();
	void BuildCell2();
	void BuildCell3();
	void BuildCell4();
	void BuildEndCell();

	void DeleteCell1();
	void DeleteCell2();
	void DeleteCell3();
	void DeleteCell4();

	void RenderGameObjects(GLuint& uniformModel, GLuint& uniformSpecularIntensity, GLuint& uniformShininessLocation);

	void CreateRandomBox();
	void CreateRandomBoxAtPos(const btVector3& pos);

	PhysicsLayer* GetPhysicsWorld() const { return physicsWorld; }

	bool GetCell3Built() const { return cell3Built; }
	bool GetCell4Built() const { return cell4Built; }

	bool GetCell1Deleted() const { return cell1Deleted; }
	bool GetCell2Deleted() const { return cell2Deleted; }
	bool GetCell3Deleted() const { return cell3Deleted; }

	CountDownTimer* GetTimer() const { return timer; }

	void SetCell3Built(bool built) { cell3Built = built; }
	void SetCell4Built(bool built) { cell4Built = built; }

private:
	// Materials
	Material dullMaterial;
	Material shinyMaterial;

	// Textures
	Texture groundCobblestoneTexture;
	Texture brick;
	Texture floorSquares;
	Texture rustTexture;
	Texture squareTechTexture1;
	Texture squareTechTexture2;
	Texture squareTechTexture3;
	Texture squareTechTexture4;
	Texture sandWhite;

	Texture screen1, screen2, screen3, screen4;

	// Models
	Model cube;
	Model rustyGate;
	Model chandelier;
	Model techPedestal;
	Model dispenserExport;

	Model Arch;
	Model Brick_Wall;
	Model Cathedral_Window;
	Model Cornice;
	Model Door;
	Model Narrow_Pillar;
	Model Pillar_Standalone;
	Model Wide_Pillar_No_Door;
	Model Wide_Pillar_With_Door;
	Model Windows;
	Model Switch_round_button;

	PhysicsLayer* physicsWorld;
	std::vector<GameObject*> nonPhysicsGameObjects;

	// Timer
	CountDownTimer* timer;

	//Displayer
	NumberDisplay* numberDisplay;

	GameObjects cell1GameObjects, cell2GameObjects, cell3GameObjects, cell4GameObjects;

	bool cell1Built, cell2Built, cell3Built, cell4Built;
	bool cell1Deleted, cell2Deleted, cell3Deleted;

	void DestroyNonPhysicsGameObject(GameObject* gameObject);

	void CreateCustomBox(std::string name, GameObject::ObjectTypes objType, const btVector3& scale, const btVector3& color, const btVector3& randomPos);
};