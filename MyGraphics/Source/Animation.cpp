#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::AddFrame(Sprite * sprite)
{
	this->sprite.push_back(sprite);
}

void Animation::SetFramerate(float frameRate)
{
	this->frameRate = frameRate;
}

int Animation::GetFrameCount()
{
	return sprite.size();
}

float Animation::GetFramerate()
{
	return frameRate;
}

float Animation::GetAnimationTime()
{
	return GetFrameCount() * GetFramerate();
}

#include "MyMath.h"

Sprite * Animation::GetFrame(float elapsedTime)
{
	return sprite[Math::Min((int)(elapsedTime / GetFramerate()), GetFrameCount())];
}
