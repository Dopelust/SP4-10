#pragma once

#include "Component.h"

class Resolution : public Component
{
public:
	Resolution() : width(1280), height(720) {}

	int width;
	int height;
};