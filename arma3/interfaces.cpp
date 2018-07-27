#include "arma3.h"

bool Interfaces::Init()
{
	world = *(World**)((DWORD64)GetModuleHandle(0) + 0x2553F48);
	if (!world)
		return false;

	network_manager = *(NetworkManager**)((DWORD64)GetModuleHandle(0) + 0x2512170);
	if (!network_manager)
		return false;

	game_state = (GameState*)((DWORD64)GetModuleHandle(0) + 0x257E5D0);
	if (!game_state)
		return false;

	return true;
}

Interfaces ints;