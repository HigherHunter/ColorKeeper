#pragma once

#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include "Window.h"
#include "TextManager.h"
#include "GameManager.h"
#include "FileManager.h"

class ScreenManager
{
public:
	ScreenManager(Window* currentWindow);

	void DisplayMainMenu(ShaderText& textShader);
	void DisplayPauseMenu(ShaderText& textShader);
	void DisplayHighScore(ShaderText& textShader);
	void DisplayCredits(ShaderText& textShader);
	void DisplayStart(ShaderText& textShader);
	void DisplayLoading(ShaderText& textShader);
	void CheckMainMenuInputEvent();
	void CheckPauseMenuInputEvent();
	void UpdateScore();

	void AddCharacterToName(char character);
	void BackspaceName();
	string GetName() const { return name; }

	map<string, int> GetHighScoreMap() const { return highScoreMap; }
	bool GetIsRestarted() { return restarted; }
	void SetRestarted(bool value) { restarted = value; }

	void StopDisplayLoading() { displayLoading = false; }

private:
	TextManager* textManager;
	Window* currentWindow;

	bool startButton, continueButton, highScoreButton, creditsButton, quitButton, exitButton, backButton, enterButton;
	bool displayHighScore, displayStart, displayCredits, displayLoading;
	bool restarted;

	string name;
	
	map<string, int> highScoreMap;
	vector < std::pair<string, int>> highScorePairs;
};