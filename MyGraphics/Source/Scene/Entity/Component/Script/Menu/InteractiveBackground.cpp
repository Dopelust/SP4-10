#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"

#include "Vector2.h"
#include "InteractiveBackground.h"

InteractiveBackground::InteractiveBackground()
{
}

InteractiveBackground::~InteractiveBackground()
{
}

#include "../../../../../Assets.h"
#include "Vector4.h"

void InteractiveBackground::Init(Entity * ent)
{
	Vector2& screen = Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas), Scene::scene->GetResolutionY(Scene::scene->canvas));

	background = 
		Scene::scene->root->AttachChild(EntityFactory::CreateGraphic(screen * 0.5f, screen * 1.1f, 
			Resource.GetTexture("NightChanges"), Vector4(1, 1, 1)));
}

#include "../../Transform.h"
#include "../../../../../InputHandler.h"

void InteractiveBackground::Update(double dt)
{
	Vector2& screen = Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas), Scene::scene->GetResolutionY(Scene::scene->canvas));
	Vector2& position = Input.GetCursorPos() * 0.05f + screen * 0.475f;

	background->transform->Position() = (screen - position).GetVector3();
}
