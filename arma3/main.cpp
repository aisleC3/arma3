#include "arma3.h"

void Init()
{
	/*AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);*/

	if(!ints.Init())
		MessageBoxA(NULL, "Interfaces: Failed to init.", NULL, NULL);

	if (!presenthook.Init())
		MessageBoxA(NULL, "PresentHook: Failed to init.", NULL, NULL);
}

DWORD __stdcall DllMain(HMODULE dll, DWORD callreason, void* reserved)
{
	if (callreason == DLL_PROCESS_ATTACH)
	{
		Init();

		return 1;
	}

	return 0;
}