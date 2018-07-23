#include "arma3.h"

using PresentType = long(__stdcall*)(IDXGISwapChain*, UINT, UINT);
PresentType original_function;

long __stdcall Present(IDXGISwapChain* swapchain, UINT syncinterval, UINT flags)
{
	static D3D11Renderer* renderer;
	if (!renderer)
	{
		renderer = new D3D11Renderer(swapchain);
		renderer->Initialize();
	}

	renderer->BeginScene();

	//if (GetAsyncKeyState(VK_RBUTTON))
	//world->GetlocalPlayer()->obj->GetFutureVisualState()->pos = vs->pos;

	entities.StoreEntities();

	for (auto player : entities.GetPlayers())
	{
		if (!player)
			continue;

		esp.Frame(renderer, player);
		aimbot.Frame(renderer, player);
		misc.Frame(renderer, player);
	}

	for(auto vehicle : entities.GetVehicles())
	{
		if (!vehicle)
			continue;

		esp.Frame(renderer, vehicle);
		misc.Frame(renderer, vehicle);
	}

	entities.ClearEntities();

	renderer->EndScene();

	return original_function(swapchain, syncinterval, flags);
}

bool PresentHook::Init()
{
	EngineDD11* engine = ints.world->GetEngine();
	if (!engine)
		return false;

	Hook* hook = new Hook(engine->swapchain, 8, &Present);
	original_function = (PresentType)hook->ReplaceVirtual();

	return true;
}

PresentHook presenthook;