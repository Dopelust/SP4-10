#pragma once

#include "../Component.h"

#include <vector>
using namespace::std;

class Resolution;
class WorldZoomScript : public Component
{
public:
	WorldZoomScript();
	~WorldZoomScript();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Resolution* resolution;
};