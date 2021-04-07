#pragma once

#include <cstdio>
#include <irrKlang.h>
using namespace irrklang;

class SoundManager
{
public:
	static SoundManager* GetInstance();

	void PlayBackgroundSound();
	void PlayCorrectSound();
	void PlayErrorSound();

private:
	static SoundManager* instance;
	SoundManager();

	ISoundEngine* soundEngine;
};