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

	for (auto player : entities.GetPlayers())
	{
		aimbot.Frame(renderer, player);

		VisualState* vs = player->GetRenderVisualState();
		if (!vs)
			continue;

		if (vs->origin == Vector(0, 0, 0))
			continue;

		//if (GetAsyncKeyState(VK_RBUTTON))
		//world->GetlocalPlayer()->obj->GetFutureVisualState()->pos = vs->pos;

		//vs->pos = Vector(0, 0, 0);

		Camera* camera = ints.world->GetCamera();
		if (!camera)
			continue;

		Vector screen;
		if (camera->WorldToScreen(vs->origin, screen))
			renderer->DrawString(12, screen.x, screen.y, Color(255, 255, 255, 255), player->GetObjectType()->type1->GetValue(), true);
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