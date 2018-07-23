#include "arma3.h"

void Misc::ImpulseAll(Object* player)
{
	ints.network_manager->AddImpulse(player, new Vector(100, 1000, 100), new Vector(1, 1, 1));
}

void Misc::Frame(D3D11Renderer* renderer, Object* player)
{
	if (GetAsyncKeyState(VK_DELETE))
	{
		renderer->DrawString(16, 5, 5, Color(255, 255, 255, 255), "Impulse", true);
		ImpulseAll(player);
	}
}

Misc misc;