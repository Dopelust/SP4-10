#pragma once

#include <string>
#include <map>
using namespace::std;

#define Audio SoundEngine::Instance()

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

struct Vector3;

class SoundEngine
{
public:
	static SoundEngine& Instance();

	void Init();

	bool IsPlaying(const char* name);
	ISound* Play2D(const char* name, float volume = 1);
	void Play3D(const char* name, const Vector3& position, float volume = 1);

private:
	SoundEngine();
	~SoundEngine();

	ISoundEngine * engine;

	vec3df GetVec3df(const Vector3& vec);
	map<string, string> audio;
};