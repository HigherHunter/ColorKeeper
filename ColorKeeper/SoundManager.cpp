#include "SoundManager.h"

SoundManager* SoundManager::instance = 0;

SoundManager::SoundManager()
{
	soundEngine = createIrrKlangDevice();

	if (!soundEngine)
	{
		printf("Sound engine startup failed \n");
	}
}

SoundManager* SoundManager::GetInstance()
{
	if (!instance)
		instance = new SoundManager();

	return instance;
}

void SoundManager::PlayBackgroundSound()
{
	ISoundSource* background = soundEngine->addSoundSourceFromFile("Assets/Audio/Music/CalmBackground.mp3");
	background->setDefaultVolume(0.7f);
	soundEngine->play2D(background, true);
}

void SoundManager::PlayCorrectSound()
{
	soundEngine->play2D("Assets/Audio/Sounds/success.wav");
}

void SoundManager::PlayErrorSound()
{
	soundEngine->play2D("Assets/Audio/Sounds/wrong.wav");
}