#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
	score = 0;
}

void ScoreManager::AddScore(int amount)
{
	score += amount;
}

void ScoreManager::SubtractScore(int amount)
{
	score -= amount;
}