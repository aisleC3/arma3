#include "arma3.h"

void Entities::StoreEntities()
{
	EntityTable* nearents = ints.world->GetNearEnts();
	if (nearents)
	{
		for (int i = 0; i < ints.world->NearEntsSize(); i++)
		{
			Entity* entity = nearents->GetEntityFromIndex(i);
			if (!entity)
				continue;

			EntityLink* link = entity->link;
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

				players.push_back(obj);
			}
		}
	}
}

void Entities::ClearEntities()
{
	players.clear();
}

std::vector<Object*> Entities::GetPlayers()
{
	return players;
}

Entities entities;