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

	entities.StoreEntities();

	for (auto container : entities.GetObjects())
	{
		if (!container)
			continue;

		Object* obj = container->GetPointer();
		if (!obj)
			continue;

		esp.Frame(renderer, obj);

		Type type = container->GetType();

		if (type == unit)
			aimbot.Frame(renderer, obj);

		if ((type == unit) || (type == vehicle))
			misc.Frame(renderer, obj);
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