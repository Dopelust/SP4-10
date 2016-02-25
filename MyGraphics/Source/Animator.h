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

private:
	map<string, Animation*> animation;
};

#endif