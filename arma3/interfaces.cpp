#include "arma3.h"

bool Interfaces::Init()
{
	world = *(World**)((DWORD64)GetModuleHandle(0) + 0x2553F48);
	if (!world)
		return false;

	return true;
}

Interfaces ints;