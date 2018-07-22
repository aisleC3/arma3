#include "arma3.h"

#include "presenthook.h"

void Init()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	if (!presenthook.Init())
		MessageBoxA(NULL, "PresentHook: Failed to init.", NULL, NULL);
}

DWORD __stdcall DllMain(HMODULE dll, DWORD callreason, void* reserved)
{
	if (callreason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(dll);
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL);

		Init();

		return 1;
	}

	return 0;
}