#include "GameManager.h"

GameManager* GameManager::instance = 0;

GameManager::GameManager()
{
	activeState = start;

	scoreManager = new ScoreManager();

	mistakeCount = 0;
}

GameManager* GameManager::GetInstance()
{
	if (!instance)
		instance = new GameManager();

	return instance;
}

void GameManager::IncreaseScore(int value)
{
	scoreManager->AddScore(value);
}

void GameManager::ProcessMistake(int value)
{
	static int increment = 20;
	
	mistakeCount++;
	if (mistakeCount >= 5)
	{
		scoreManager->SubtractScore(value + increment);
		increment += 20;
	}
	else
		scoreManager->SubtractScore(value);
}