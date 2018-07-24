#include "arma3.h"

std::vector<Entity*> ents;

void Entities::StoreEntities()
{
	EntityTable* nearents = ints.world->GetNearEnts();
	EntityTable* farents = ints.world->GetFarEnts();
	if (nearents && farents)
	{
		for (int i = 0; i < ints.world->NearEntsSize(); i++)
		{
			Entity* entity = nearents->GetEntityFromIndex(i);
			if (entity) ents.push_back(entity);
		}

		for (int i = 0; i < ints.world->FarEntsSize(); i++)
		{
			Entity* entity = farents->GetEntityFromIndex(i);
			if (entity) ents.push_back(entity);
		}
	}

	for (auto ent : ents)
	{
		EntityLink* link = ent->link;
		if (!link)
			continue;

		if (ints.world->GetlocalPlayer() == link)
			continue;

		Object* obj = link->obj;
		if (!obj)
			continue;

		if (strstr(obj->GetObjectType()->type3->GetValue().c_str(), "infantry"))
		{
			if (obj->IsDead())
				continue;

			objs.push_back(new ObjectContainer(unit, obj));

			continue;
		}

		if (strstr(obj->GetObjectType()->type3->GetValue().c_str(), "vehicle") || strstr(obj->GetObjectType()->type3->GetValue().c_str(), "air"))
		{
			if (obj->IsDead())
				continue;

			objs.push_back(new ObjectContainer(vehicle, obj));

			continue;
		}
	}

	ents.clear();
}

void Entities::ClearEntities()
{
	objs.clear();
}

std::vector<ObjectContainer*> Entities::GetObjects()
{
	return objs;
}

Entities entities;