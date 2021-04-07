#pragma once

#include <chrono>
#include <vector>
#include <GL/glew.h>
#include "btBulletDynamicsCommon.h"
#include "Material.h"
#include "Texture.h"
#include "GameObject.h"

using namespace std::chrono;

class CountDownTimer
{
public:
	CountDownTimer(int seconds, const btVector3& position, Material& mat);

	void CalculateTime();
	void RenderTimer(GLuint& unifModel, GLuint& unifSpecularIntensity, GLuint& unifShininessLocation);
	void ReduceTime(int amount);

	bool HasEnded() { return hasEnded; }

private:

	system_clock::time_point start, over;

	int totalTime;

	std::vector<int> timerDigits;

	std::vector<GameObject*> timerDigitsObjects;

	bool hasEnded;

	Texture digitsTexture[10];

	void LoadDigitTextures();
	void GetTimeDigits(std::vector<int>& digits, int num);
};