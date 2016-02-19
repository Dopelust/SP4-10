#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../Component.h"

class PlayerController :
	public Component
{
public:
	PlayerController();
	~PlayerController();

	int gold;
	int stage;
	int wave;
	int baseHealth;
};

#endif