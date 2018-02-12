#pragma once

#include "SingletonTemplate.h"
#include <irrKlang.h>
using namespace irrklang;
#include <map>

class SoundEngine : public Singleton<SoundEngine>
{
protected:
	// Destructor
	ISoundEngine* theSoundEngine;

	// The library map of all the sounds created
	std::map<std::string, std::string> soundMap;

public:
	// Constructor
	SoundEngine();
	virtual ~SoundEngine();

	// Init this class and it will create the Sound Engine
	bool Init(void);

	// Get the handler to the sound engine
	ISoundEngine* GetSoundEngine(void);

	// Add a sound to this library
	void AddSound(const std::string& _soundIndex, const std::string& _soundSource);
	// Get a sound from this map 
	std::string GetSound(const std::string& _soundIndex);
	// Remove a sound from this map
	bool RemoveSound(const std::string& _soundIndex);
	// Play a sound from this map
	void PlayASound(const std::string& _soundIndex);
};
