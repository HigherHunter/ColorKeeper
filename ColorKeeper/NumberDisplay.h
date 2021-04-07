#pragma once

#include "Texture.h"
#include "GameObject.h"

class NumberDisplay
{
public:
	NumberDisplay(int score, const btVector3& position, Material& mat);
	void RenderNumber(GLuint& unifModel, GLuint& unifSpecularIntensity, GLuint& unifShininessLocation);

private:
	std::vector<int> timerDigits;

	std::vector<GameObject*> timerDigitsObjects;

	Texture digitsTexture[10];

	void LoadDigitTextures();

	void Getigits(std::vector<int>& digits, int num);
};