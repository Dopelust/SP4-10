#pragma once

#include "Component.h"

#define uploadRate 0.25f

class Transform;
class NetworkObject : public Component
{
public:
	NetworkObject();
	~NetworkObject();

	Transform* GetTransform();

	void Init(Entity* root);
	void Update(double dt);

private:
	Transform* client;
	Transform* server;
};