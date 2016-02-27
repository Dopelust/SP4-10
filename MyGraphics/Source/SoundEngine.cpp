#include "SoundEngine.h"
#include "Scene\Camera.h"

#define camera Camera::current

bool SoundEngine::IsPlaying(const char * name)
{
	return engine->isCurrentlyPlaying(audio[name].c_str());
}

bool SoundEngine::IsPlaying(const SoundPack & sound)
{
	for (auto& s : sound.GetSounds())
	{
		if (IsPlaying(s.c_str()))
			return true;
	}

	return false;
}

Sound * SoundEngine::GetSound(const char * name)
{
	return nullptr;
}

Sound* SoundEngine::Play2D(const char * name, float volume)
{
	Sound * sound = (Sound*)engine->play2D(audio[name].c_str(), false, true);

	if (sound)
	{
		sound->setVolume(volume);
		sound->setIsPaused(false);

		return sound;
	}

	return NULL;
}

Sound * SoundEngine::Play2D(const SoundPack & sound, float volume)
{
	Sound * snd = (Sound*)engine->play2D(sound.GetSound().c_str(), false, true);

	if (snd)
	{
		snd->setVolume(volume);
		snd->setIsPaused(false);

		return snd;
	}

	return NULL;
}

void SoundEngine::StopPlaying(Sound* sound)
{
	if (sound)
	{
		sound->stop();
		sound->drop();
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

const SoundPack & SoundEngine::GetSoundPack(const char * name)
{
	return soundPack[name];
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
	audio["hover"] = "Assets//Sound//hover.ogg";

	audio["bubble"] = "Assets//Sound//bubble.mp3";
	audio["splash"] = "Assets//Sound//splash.mp3";
	audio["Night Changes"] = "Assets//Sound//NightChanges.mp3";

	soundPack["bgm"].AddSound("Assets//Sound//bgm//war1.mp3");
	soundPack["bgm"].AddSound("Assets//Sound//bgm//war2.mp3");
	soundPack["bgm"].AddSound("Assets//Sound//bgm//war3.mp3");

	soundPack["build"].AddSound("Assets//Sound//tower//build1.mp3");
	soundPack["build"].AddSound("Assets//Sound//tower//build2.mp3");

	soundPack["sell"].AddSound("Assets//Sound//tower//sell1.mp3");
}

void SoundEngine::SetVolume(float volume)
{
	engine->setSoundVolume(volume);
}

vec3df SoundEngine::GetVec3df(const Vector3 & vec)
{
	return vec3df(vec.x, vec.y, vec.z);
}

SoundPack::SoundPack()
{
}

SoundPack::~SoundPack()
{
}

void SoundPack::AddSound(const char * filepath)
{
	sounds.push_back(filepath);
}

const vector<string>& SoundPack::GetSounds() const
{
	return sounds;
}

const string & SoundPack::GetSound() const
{
	if (sounds.size())
		return sounds[rand() % sounds.size()];

	return "";
}

Sound::Sound()
{
}

Sound::~Sound()
{
}
