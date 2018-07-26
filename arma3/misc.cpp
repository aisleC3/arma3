#include "arma3.h"

void Misc::ImpulseAll(Object* player)
{
	ints.network_manager->AddImpulse(player, new Vector(100000, 100000, 100000), new Vector(100, 100000, 100));
}

void Misc::InfiniteStamina()
{
	if(ints.world->GetlocalPlayer()->obj)
	{
		ints.world->GetlocalPlayer()->obj->SetEnableFatigue(false);
	}
}

void Misc::WeaponHacks()
{
	Object* local = ints.world->GetlocalPlayer()->obj;
	if (local)
	{
		/* No Recoil */
		local->SetUnitRecoilCoefficient(0.f);

		/* No Spread? */
		local->SetCustomAimCoef(0.f);
	}
}

void Misc::DeleteAllBackpacks(Object* player)
{
	if (player)
		ints.network_manager->DeleteBackpack(player);
}

void Misc::Frame(D3D11Renderer* renderer, Object* player)
{
	if (GetAsyncKeyState(VK_DELETE))
	{
		renderer->DrawString(16, 5, 5, Color(255, 255, 255, 255), "Impulse", true);
		ImpulseAll(player);
	}

	InfiniteStamina();
	WeaponHacks();
	DeleteAllBackpacks(player); // we're going to need to add keybinds lol
}

Misc misc;