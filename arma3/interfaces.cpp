#include "arma3.h"

bool Interfaces::Init()
{
	game_base = (DWORD64)Memory::GetModuleBaseAddress("arma3_x64.exe");
	if (!game_base)
		return false;

	world = *(World**)(game_base + 0x2553F48);
	if (!world)
		return false;

	network_manager = *(NetworkManager**)(game_base + 0x2512170);
	if (!network_manager)
		return false;

	game_state = (GameState*)(game_base + 0x257E5D0);
	if (!game_state)
		return false;

	return true;
}

Interfaces ints;