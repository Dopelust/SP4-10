#include "SoundEngine.h"
#include "Scene\Camera.h"

#define camera Camera::current

void SoundEngine::Play2D(const char * name, float volume)
{
	ISound * sound = engine->play2D(audio[name].c_str(), false, true);
	if (sound)
	{
		sound->setVolume(volume);
		sound->setIsPaused(false);
	}
}

void SoundEngine::Play3D(const char * name, const Vector3& position, float volume)
{
	engine->setListenerPosition(GetVec3df(camera->position), GetVec3df(camera->direction));

	ISound * sound = engine->play3D(audio[name].c_str(), GetVec3df(position), false, true);
	if (sound)
	{
		sound->setVolume(volume);
		sound->setIsPaused(false);
	}
}

SoundEngine::SoundEngine() : engine(NULL)
{
	engine = createIrrKlangDevice();
}

SoundEngine::~SoundEngine()
{		
	if (engine)
		engine->drop();
}

SoundEngine & SoundEngine::Instance()
{
	static SoundEngine sound;
	return sound;
}

void SoundEngine::Init()
{
	audio["click"] = "Assets//Sound//click.ogg";
}

vec3df SoundEngine::GetVec3df(const Vector3 & vec)
{
	return vec3df(vec.x, vec.y, vec.z);
}
