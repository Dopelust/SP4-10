#pragma once

#include <string>
#include <map>
#include <vector>
using namespace::std;

#define Audio SoundEngine::Instance()

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

struct Vector3;

class Sound : public ISound
{
public:
	Sound();
	~Sound();
};

class SoundPack
{
public:
	SoundPack();
	~SoundPack();

	void AddSound(const char* filepath);

	const vector<string>& GetSounds() const;
	const string& GetSound() const;

private:
	vector<string> sounds;
};

class SoundEngine
{
public:
	static SoundEngine& Instance();

	void Init();

	void SetVolume(float volume);

	bool IsPlaying(const char* name);
	bool IsPlaying(const SoundPack& sound);

	Sound* GetSound(const char* name);

	Sound* Play2D(const char* name, float volume = 1);
	Sound* Play2D(const SoundPack& sound, float volume = 1);

	void StopPlaying(Sound* sound);

	void Play3D(const char* name, const Vector3& position, float volume = 1);
	const SoundPack& GetSoundPack(const char* name);

private:
	SoundEngine();
	~SoundEngine();

	ISoundEngine * engine;

	vec3df GetVec3df(const Vector3& vec);

	map<string, string> audio;
	map<string, SoundPack> soundPack;
};