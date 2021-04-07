#include "ScreenManager.h"

ScreenManager::ScreenManager(Window* currentWindow):
startButton(false), continueButton(false), highScoreButton(false), creditsButton(false), quitButton(false), exitButton(false), backButton(false), enterButton(false), displayHighScore(false), displayStart(false), displayCredits(false), displayLoading(false), restarted(false)
{
	this->currentWindow = currentWindow;

	textManager = new TextManager();
	textManager->LoadTextCharacters();
	
	if (!FileManager::ReadMap("highScore.txt", highScoreMap))
		std::cout << "Error: Cant read highScore.txt file" << std::endl;
	
	for (auto itr = highScoreMap.begin(); itr != highScoreMap.end(); ++itr)
	{
		highScorePairs.push_back(*itr);
	}
	std::sort(highScorePairs.begin(), highScorePairs.end(), [](auto& left, auto& right) {
		return left.second > right.second;
		});
}

void ScreenManager::DisplayMainMenu(ShaderText& textShader)
{
	if (displayHighScore)
		DisplayHighScore(textShader);
	else if (displayStart)
		DisplayStart(textShader);
	else if (displayCredits)
		DisplayCredits(textShader);
	else if (displayLoading)
		DisplayLoading(textShader);
	else
	{
		// Set OpenGL options
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if
			(textManager->RenderTextMiddle(
				textShader, "Start",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f + 120, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			startButton = true;
		else
			startButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "High Score",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f + 40, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			highScoreButton = true;
		else
			highScoreButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "Credits",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - 40, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			creditsButton = true;
		else
			creditsButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "Exit",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - 120, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			exitButton = true;
		else
			exitButton = false;

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}

void ScreenManager::DisplayPauseMenu(ShaderText& textShader)
{
	if (displayHighScore)
		DisplayHighScore(textShader);
	else if (displayCredits)
		DisplayCredits(textShader);
	else
	{
		// Set OpenGL options
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if
			(textManager->RenderTextMiddle(
				textShader, "Resume",
				currentWindow->GetBufferWidth() / 2.0f - 20, currentWindow->GetBufferHeight() / 2.0f + 120, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			continueButton = true;
		else
			continueButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "High Score",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f + 40, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			highScoreButton = true;
		else
			highScoreButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "Credits",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - 40, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			creditsButton = true;
		else
			creditsButton = false;

		if
			(textManager->RenderTextMiddle(
				textShader, "Quit",
				currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - 120, 1.0f,
				glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
				glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
			quitButton = true;
		else
			quitButton = false;

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}

void ScreenManager::DisplayHighScore(ShaderText& textShader)
{
	// Set OpenGL options
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int offset = 80;
	int maxDisplayedNamesCount = 0;
	
	for (auto itr = highScorePairs.begin(); itr != highScorePairs.end(); ++itr)
	{
		textManager->RenderTextEnd(
			textShader, itr->first,
			currentWindow->GetBufferWidth() / 2.0f - 40, currentWindow->GetBufferHeight() - offset, 1.0f,
			glm::vec3(0.3, 0.7f, 0.9f));

		textManager->RenderText(
			textShader, std::to_string(itr->second),
			currentWindow->GetBufferWidth() / 2.0f + 40, currentWindow->GetBufferHeight() - offset, 1.0f,
			glm::vec3(0.3, 0.7f, 0.9f));

		offset += 80;
		maxDisplayedNamesCount++;
		if (maxDisplayedNamesCount == 5)
			break;
	}
	
	if
		(textManager->RenderTextMiddle(
			textShader, "Back",
			currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - currentWindow->GetBufferHeight() / 4.0f, 1.0f,
			glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
			glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
		backButton = true;
	else
		backButton = false;

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void ScreenManager::DisplayStart(ShaderText& textShader)
{
	// Set OpenGL options
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	textManager->RenderTextMiddle(
		textShader, "Enter your name:",
		currentWindow->GetBufferWidth() / 2.0f + 20, currentWindow->GetBufferHeight() / 2.0f + currentWindow->GetBufferHeight() / 4.0f, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	textManager->RenderTextMiddle(
		textShader, "_______________",
		currentWindow->GetBufferWidth() / 2.0f - 10, currentWindow->GetBufferHeight() / 2.0f, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	textManager->RenderTextMiddle(
		textShader, name,
		currentWindow->GetBufferWidth() / 2.0f - 10, currentWindow->GetBufferHeight() / 2.0f + 20, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	if
		(textManager->RenderTextMiddle(
			textShader, "Enter",
			currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - currentWindow->GetBufferHeight() / 4.0f, 1.0f,
			glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
			glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
		enterButton = true;
	else
		enterButton = false;

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void ScreenManager::DisplayCredits(ShaderText& textShader)
{
	// Set OpenGL options
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	textManager->RenderTextMiddle(
		textShader, "Color Defender",
		currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f + currentWindow->GetBufferHeight() / 3.0f, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	textManager->RenderTextMiddle(
		textShader, "OpenGL demo game about",
		currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f + 60, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));
	textManager->RenderTextMiddle(
		textShader, "colors and interaction.",
		currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));
	
	textManager->RenderTextMiddle(
		textShader, "Made by:",
		currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - currentWindow->GetBufferHeight() / 5.0f, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	textManager->RenderTextMiddle(
		textShader, "Borko Dimitrijevic",
		currentWindow->GetBufferWidth() / 2.0f + 30, currentWindow->GetBufferHeight() / 2.0f - currentWindow->GetBufferHeight() / 5.0f - 60, 1.0f,
		glm::vec3(0.3, 0.7f, 0.9f));

	if
		(textManager->RenderTextMiddle(
			textShader, "Back",
			currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f - currentWindow->GetBufferHeight() / 4.0f - 120, 1.0f,
			glm::vec3(0.3, 0.7f, 0.9f), glm::vec3(0.5, 0.8f, 0.2f),
			glm::vec2(currentWindow->GetMouseXPos(), currentWindow->GetBufferHeight() - currentWindow->GetMouseYPos())))
		backButton = true;
	else
		backButton = false;
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void ScreenManager::DisplayLoading(ShaderText& textShader)
{
	// Set OpenGL options
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	textManager->RenderTextMiddle(
		textShader, "Loading...",
		currentWindow->GetBufferWidth() / 2.0f, currentWindow->GetBufferHeight() / 2.0f, 1.5f,
		glm::vec3(0.3, 0.7f, 0.9f));

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void ScreenManager::CheckMainMenuInputEvent()
{
	if (startButton)
	{
		displayStart = true;
	}
	else if (highScoreButton)
	{
		displayHighScore = true;
	}
	else if (creditsButton)
	{
		displayCredits = true;
	}
	else if (exitButton)
	{
		currentWindow->CloseWindow();
	}
	else if (backButton)
	{
		if (displayHighScore)
			displayHighScore = false;
		else if (displayCredits)
			displayCredits = false;
	}
	else if (enterButton)
	{
		displayStart = false;
		displayLoading = true;
		restarted = true;
		GameManager::GetInstance()->SetActiveState(GameManager::inGame);
	}

	startButton = false, highScoreButton = false, creditsButton = false, exitButton = false, backButton = false;
}

void ScreenManager::CheckPauseMenuInputEvent()
{
	if (continueButton)
	{
		GameManager::GetInstance()->SetActiveState(GameManager::inGame);
	}
	else if (highScoreButton)
	{
		displayHighScore = true;
	}
	else if (creditsButton)
	{
		displayCredits = true;
	}
	else if (quitButton)
	{
		GameManager::GetInstance()->SetActiveState(GameManager::start);
	}
	else if (backButton)
	{
		if (displayHighScore)
			displayHighScore = false;
		else if (displayCredits)
			displayCredits = false;
	}

	continueButton = false, highScoreButton = false, creditsButton = false, quitButton = false;
}

void ScreenManager::UpdateScore()
{
	highScoreMap.clear();
	highScorePairs.clear();
	
	if (!FileManager::ReadMap("highScore.txt", highScoreMap))
		std::cout << "Error: Cant read highScore.txt file" << std::endl;

	for (auto itr = highScoreMap.begin(); itr != highScoreMap.end(); ++itr)
	{
		highScorePairs.push_back(*itr);
	}
	std::sort(highScorePairs.begin(), highScorePairs.end(), [](auto& left, auto& right) {
		return left.second > right.second;
		});
}

void ScreenManager::AddCharacterToName(char character)
{
	if (name.length() < 10)
		name += character;
}

void ScreenManager::BackspaceName()
{
	if (name.length() > 0)
		name.pop_back();
}