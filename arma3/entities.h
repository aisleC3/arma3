#pragma once

enum Type
{
	unit,
	vehicle,
	animal,
	other,
	none
};

class ObjectContainer
{
private:
	Type type = none;
	Object* pointer = nullptr;
public:
	Type GetType() { return type; }
	Object* GetPointer() { return pointer; }

	void SetType(Type t) { type = t; }
	void SetPointer(Object* p) { pointer = p; }

	ObjectContainer(Type t, Object* p)
	{
		type = t;
		pointer = p;
	}
};

class Entities
{
private:
	std::vector<ObjectContainer*> objs;

public:

	std::vector<ObjectContainer*> GetObjects();

	bool Init();
	void StoreEntities();
	void ClearEntities();
};

extern Entities entities;