#pragma once

class ScoreManager
{
public:
	ScoreManager();

	void AddScore(int amount);
	void SubtractScore(int amount);
	void ResetScore() { score = 0; }

	int GetScore() { return score; }

private:
	int score;
};