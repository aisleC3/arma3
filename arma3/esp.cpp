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
		renderer->DrawString(12, screen.x, screen.y, Color(255, 255, 255, 255), player->GetObjectType()->type1->GetValue(), true);
}

ESP esp;