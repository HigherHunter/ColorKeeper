#include "CountdownTimer.h"

CountDownTimer::CountDownTimer(int seconds, const btVector3& position, Material& mat)
{
	LoadDigitTextures();

	btVector3 pos = position;
	pos.setZ(pos.getZ() + 3);

	GameObject* number1 = new GameObject(Shapes::squareStretch, GameObject::env, btVector3(1, 1, 1), digitsTexture[0], mat, btVector3(1, 1, 1), pos);
	number1->AddRotation(glm::vec3(1, 0, 0), 90);
	number1->AddRotation(glm::vec3(0, 0, 1), -90);
	number1->SetUseMaterial(true);
	timerDigitsObjects.push_back(number1);

	pos = position;
	pos.setZ(pos.getZ() + 1);

	GameObject* number2 = new GameObject(Shapes::squareStretch, GameObject::env, btVector3(1, 1, 1), digitsTexture[0], mat, btVector3(1, 1, 1), pos);
	number2->AddRotation(glm::vec3(1, 0, 0), 90);
	number2->AddRotation(glm::vec3(0, 0, 1), -90);
	number2->SetUseMaterial(true);
	timerDigitsObjects.push_back(number2);

	pos = position;
	pos.setZ(pos.getZ() - 1);

	GameObject* number3 = new GameObject(Shapes::squareStretch, GameObject::env, btVector3(1, 1, 1), digitsTexture[0], mat, btVector3(1, 1, 1), pos);
	number3->AddRotation(glm::vec3(1, 0, 0), 90);
	number3->AddRotation(glm::vec3(0, 0, 1), -90);
	number3->SetUseMaterial(true);
	timerDigitsObjects.push_back(number3);

	pos = position;
	pos.setZ(pos.getZ() - 3);

	GameObject* number4 = new GameObject(Shapes::squareStretch, GameObject::env, btVector3(1, 1, 1), digitsTexture[0], mat, btVector3(1, 1, 1), pos);
	number4->AddRotation(glm::vec3(1, 0, 0), 90);
	number4->AddRotation(glm::vec3(0, 0, 1), -90);
	number4->SetUseMaterial(true);
	timerDigitsObjects.push_back(number4);

	totalTime = seconds;

	GetTimeDigits(timerDigits, totalTime);

	hasEnded = false;

	start = system_clock::now();
}

void CountDownTimer::CalculateTime()
{
	if (totalTime > 0)
	{
		over = system_clock::now();
		const duration<int> timeSpan = duration_cast<duration<int>>(over - start);

		if (timeSpan.count() >= 1)
		{
			totalTime--;
			start = over;
			timerDigits.clear();
			GetTimeDigits(timerDigits, totalTime);
		}
	}
	else
	{
		hasEnded = true;
	}
}

void CountDownTimer::RenderTimer(GLuint& unifModel, GLuint& unifSpecularIntensity, GLuint& unifShininessLocation)
{
	for (int i = 0; i < timerDigits.size(); i++)
	{
		
		switch (timerDigits[i])
		{
		case 0:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[0]);
			break;
		case 1:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[1]);
			break;
		case 2:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[2]);
			break;
		case 3:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[3]);
			break;
		case 4:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[4]);
			break;
		case 5:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[5]);
			break;
		case 6:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[6]);
			break;
		case 7:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[7]);
			break;
		case 8:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[8]);
			break;
		case 9:
			timerDigitsObjects[i]->ChangeTexture(digitsTexture[9]);
			break;
		}
		timerDigitsObjects[i]->RenderGameObject(unifModel, unifSpecularIntensity, unifShininessLocation);
	}
}

void CountDownTimer::ReduceTime(int amount)
{
	totalTime -= amount;
}

void CountDownTimer::GetTimeDigits(std::vector<int>& digits, int num)
{
	if (num > 9) {
		GetTimeDigits(digits, num / 10);
	}
	digits.push_back(num % 10);
}

void CountDownTimer::LoadDigitTextures()
{
	digitsTexture[0] = Texture("Assets/Textures/Numbers/0.png");
	digitsTexture[0].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[1] = Texture("Assets/Textures/Numbers/1.png");
	digitsTexture[1].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[2] = Texture("Assets/Textures/Numbers/2.png");
	digitsTexture[2].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[3] = Texture("Assets/Textures/Numbers/3.png");
	digitsTexture[3].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[4] = Texture("Assets/Textures/Numbers/4.png");
	digitsTexture[4].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[5] = Texture("Assets/Textures/Numbers/5.png");
	digitsTexture[5].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[6] = Texture("Assets/Textures/Numbers/6.png");
	digitsTexture[6].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[7] = Texture("Assets/Textures/Numbers/7.png");
	digitsTexture[7].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[8] = Texture("Assets/Textures/Numbers/8.png");
	digitsTexture[8].LoadTextureWithAlpha(GL_CLAMP);

	digitsTexture[9] = Texture("Assets/Textures/Numbers/9.png");
	digitsTexture[9].LoadTextureWithAlpha(GL_CLAMP);
}