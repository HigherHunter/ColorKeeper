#pragma once

#include "ScoreManager.h"

class GameManager
{
public:
	static GameManager* GetInstance();
	
	enum GameState { start, inGame, paused };

	void SetActiveState(GameState state) { activeState = state; }
	GameState GetActiveState() const { return activeState; }

	void IncreaseScore(int value);
	void ProcessMistake(int value);
	void ResetMistakeCount() { mistakeCount = 0; };

	ScoreManager* GetScoreManager() { return scoreManager; }
	unsigned int GetMistakeCount() { return mistakeCount; }
	
private:
	static GameManager* instance;
	GameManager();
	
	GameState activeState;

	ScoreManager* scoreManager;

	unsigned int mistakeCount;
};