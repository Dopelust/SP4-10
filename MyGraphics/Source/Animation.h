#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
using namespace::std;

class Sprite;
class Animation
{
public:
	Animation();
	~Animation();

	void AddFrame(Sprite* sprite);
	void SetFramerate(float frameRate);

	int GetFrameCount();
	float GetFramerate();
	float GetAnimationTime();

	Sprite* GetFrame(float elapsedTime);

private:
	vector<Sprite*> sprite;
	float frameRate;
};

#endif