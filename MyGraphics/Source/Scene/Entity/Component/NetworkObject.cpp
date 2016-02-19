#include "NetworkObject.h"
#include "../Entity.h"
#include "Transform.h"

NetworkObject::NetworkObject()
{
}

NetworkObject::~NetworkObject()
{
}

Transform * NetworkObject::GetTransform()
{
	return server;
}

void NetworkObject::Init(Entity * root)
{
	client = root->transform;

	server = new Transform();
	server->Position() = client->Position();
	server->Rotation() = client->Rotation();
	server->Size() = client->Size();
}

void NetworkObject::Update(double dt)
{
	client->Position() += (server->Position() - client->Position()) * dt / uploadRate;
	client->Rotation() += (server->Rotation() - client->Rotation()) * dt / uploadRate;
	client->Size() += (server->Size() - client->Size()) * dt / uploadRate;
}
