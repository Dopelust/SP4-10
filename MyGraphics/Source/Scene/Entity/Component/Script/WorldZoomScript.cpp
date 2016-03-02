#include "WorldZoomScript.h"
#include "Vector2.h"
#include "../../../../InputHandler.h"
#include "../Resolution.h"
#include "../../Entity.h"

#include "../../../Scene.h"
#include "../GUI/Canvas.h"


WorldZoomScript::WorldZoomScript()
{
}

WorldZoomScript::~WorldZoomScript()
{
}

void WorldZoomScript::Init(Entity* entity)
{
	resolution = entity->GetComponent<Resolution>();
}

void WorldZoomScript::Update(double dt)
{
	if (Canvas.GetPopup())
		return;

	if (Input.GetScroll().y)
	{
		resolution->width -= Input.GetScroll().y * 2048 * dt;
		resolution->height = resolution->width * 9.f / 16;
	}
}