#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <string>
#include <map>
using namespace::std;

class Sprite;
class Animation;
class Animator
{
public:
	Animator();
	~Animator();

	void AddAnimation(const char* name, Animation* anim);
	Animation* GetAnimation(const char* name);

	Sprite* GetFrame();
	void Play(const char* name);
	void Update(float dt);

private:
	map<string, Animation*> animation;
	Animation* active;
	float frameTimer;
};

#endif