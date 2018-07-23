#include "arma3.h"

void Aimbot::Frame(D3D11Renderer* renderer, Object* player)
{
	EntityTable* bullets = ints.world->GetBullets();
	static int size;

	if (bullets && (size < ints.world->BulletsSize()))
	{
		for (int i = 0; i < ints.world->BulletsSize(); i++)
		{
			Entity* entity = bullets->GetEntityFromIndex(i);
			if (!entity)
				continue;

			EntityLink* link = entity->link;
			if (!link)
				continue;

			Object* obj = link->obj;
			if (!obj)
				continue;

			VisualState* vs = obj->GetFutureVisualState();
			if (!vs)
				continue;

			VisualState* vs_player = player->GetRenderVisualState();
			if (!vs_player)
				continue;

			vs->origin = vs_player->head;

			break;
		}
	}

	size = ints.world->BulletsSize();
}

Aimbot aimbot;