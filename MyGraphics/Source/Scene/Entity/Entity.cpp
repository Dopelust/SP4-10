#include "Entity.h"
#include "Component/Transform.h"

int Entity::id_count = 0;

Entity::Entity(string name) : parent(NULL), name(name), id(id_count), active(true)
{
	transform = AddComponent<Transform>();
	++id_count;
}

Entity::~Entity()
{
	while (component.size() > 0)
	{
		delete component.back();
		component.pop_back();
	}

	while (children.size() > 0)
	{
		delete children.back();
		children.pop_back();
	}
}

Entity * Entity::AttachChild(Entity * child)
{
	children.push_back(child);
	child->parent = this;
	child->transform->Init(child);

	return child;
}

Entity * Entity::DetachChild(int id)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (children[i]->id == id)
		{
			Entity* child = children[i];
			children.erase(children.begin() + i);
			return child;
		}
	}

	return NULL;
}

Entity * Entity::DetachChild(const char * name)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (children[i]->name == name)
		{
			Entity* child = children[i];
			children.erase(children.begin() + i);
			return child;
		}
	}

	return NULL;
}

Entity* Entity::AddChild(const char* name)
{
	return AttachChild(new Entity(name));
}

bool Entity::RemoveChild(int id)
{
	Entity* child = DetachChild(id);

	if (child)
	{
		delete child;
		return true;
	}

	return false;
}

bool Entity::RemoveChild(const char* name)
{
	Entity* child = DetachChild(name);

	if (child)
	{
		delete child;
		return true;
	}

	return false;
}

bool Entity::RemoveChild(Entity * child)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (child == children[i])
		{
			children.erase(children.begin() + i);
			return true;
		}
	}
	return false;
}

#include "EntityFactory.h"

Entity * Entity::GetChild(int id)
{
	for (auto& child : children)
	{
		if (child->id == id)
			return child;
	}

	for (auto& child : EntityFactory::toGenerate[this])
	{
		if (child->id == id)
			return child;
	}

	return NULL;
}

Entity * Entity::GetChild(const char* name)
{
	for (auto& child : children)
	{
		if (child->name == name)
			return child;
	}

	for (auto& child : EntityFactory::toGenerate[this])
	{
		if (child->name == name)
			return child;
	}

	return NULL;
}

vector<Entity*>& Entity::GetChildren()
{
	return children;
}

void Entity::RemoveChildren()
{
	for (auto& child : children)
		delete child;
	children.clear();
}

bool Entity::IsActive()
{
	return active;
}

void Entity::SetActive(bool active)
{
	this->active = active;
}

string Entity::GetName()
{
	return name;
}

void Entity::Rename(string name)
{
	this->name = name;
}

int Entity::GetID()
{
	return id;
}

void Entity::AssignID(int id)
{
	this->id = id;
}

void Entity::Update(double dt)
{
	for (auto& comp : component)
	{
		if (comp->IsActive())
			comp->Update(dt);
	}

	for (auto& child : children)
		if (child->IsActive())
			child->Update(dt);
}

void Entity::Draw(Mtx44& parent)
{
	parent = parent * transform->T();

	Mtx44 mat = parent * transform->R() * transform->S();
	for (auto& comp : component)
	{
		if (comp->IsActive())
			comp->Draw(mat);
	}

	for (auto& child : children)
	{
		if (child->IsActive())
		{
			Mtx44 cpy(parent);
			child->Draw(cpy);
		}
	}
}

void Entity::OnCollisionEnter(const Collision& col)
{
	for (auto& comp : component)
	{
		if (comp->IsActive())
			comp->OnCollisionEnter(col);
	}
}
