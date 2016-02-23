#ifndef ENTITY_H
#define ENTITY_H

#include "Mtx44.h"

#include <vector>
using namespace::std;

struct Collision;
class Component;
class Transform;

class Entity
{
public:
	Entity(string name = "");
	 ~Entity();

	 void Update(double dt);
	 void Draw(Mtx44& parent);

	 void OnCollisionEnter(const Collision& col);

	 Entity* AttachChild(Entity* child);
	 Entity* AddChild(const char* name);

	 Entity* DetachChild(int id);
	 Entity* DetachChild(const char* name);

	 bool RemoveChild(int id);
	 bool RemoveChild(const char* name);
	 bool RemoveChild(Entity* child);

	 Entity* GetChild(int id);
	 Entity* GetChild(const char* name);
	 vector<Entity*>& GetChildren();

	 void RemoveChildren();
	 
	 template<typename T> T* AddComponent()
	 {
		 if (!GetComponent<T>())
		 {
			 T* comp = new T();

			 component.push_back(comp);
			 comp->Init(this);

			 return comp;
		 }

		 return NULL;
	 }

	 template<typename T> T* GetComponent()
	 {
		 for (auto& comp : component)
		 {
			 if (typeid(*comp) == typeid(T))
				 return static_cast<T*>(comp);
		 }

		 return NULL;
	 }

	 Entity* parent;
	 Transform* transform;

	 bool IsActive();
	 void SetActive(bool active);
	 
	 string GetName();
	 void Rename(string name);

	 int GetID();
	 void AssignID(int id);

private:
	string name;
	int id;
	bool active;

	vector<Entity*> children;
	vector<Component*> component;

	static int id_count;
};

#endif