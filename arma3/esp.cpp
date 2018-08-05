#include "arma3.h"

void ESP::Frame(D3D11Renderer* renderer, Object* player)
{
	VisualState* vs = player->GetRenderVisualState();
	if (!vs)
		return;

	Camera* camera = ints.world->GetCamera();
	if (!camera)
		return;

	Vector screen;
	if (camera->WorldToScreen(vs->origin, screen))
	{
		std::string name;
		if (player->GetNetID()) // is an actual player?
		{
			NetworkClient* client = ints.network_manager->GetScoreboard()->GetClient(player->GetNetID());
			name = client->GetName()->GetValue();
		}
		else
			name = player->GetObjectType()->type1->GetValue();

		renderer->DrawString(12, screen.x, screen.y, Color(255, 255, 255, 255), name, true);
	}
}

ESP esp;