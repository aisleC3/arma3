#include "presenthook.h"

using PresentType = long(__stdcall*)(IDXGISwapChain*, UINT, UINT);
PresentType original_function;

World* world = nullptr;
NetworkManager* networkmanager = nullptr;

long __stdcall Present(IDXGISwapChain* swapchain, UINT syncinterval, UINT flags)
{
	static D3D11Renderer* renderer;
	if (!renderer)
	{
		renderer = new D3D11Renderer(swapchain);
		renderer->Initialize();
	}

	renderer->BeginScene();

	if (world)
	{
		EntityTable* nearents = world->GetNearEnts();
		if (nearents)
		{
			for (int i = 0; i < world->NearEntsSize(); i++)
			{
				Entity* entity = nearents->GetEntityFromIndex(i);
				if (!entity)
					continue;

				EntityLink* link = entity->link;
				if (!link)
					continue;

				if (world->GetlocalPlayer() == link)
					continue;

				Object* obj = link->obj;
				if (!obj)
					continue;

				if (obj->GetObjectType()->type1->GetValue() == "Ground")
					continue;

				if (obj->IsDead())
					continue;

				VisualState* vs = obj->GetRenderVisualState();
				if (!vs)
					continue;

				if (vs->origin == Vector(0, 0, 0))
					continue;

				//if (GetAsyncKeyState(VK_RBUTTON))
					//world->GetlocalPlayer()->obj->GetFutureVisualState()->pos = vs->pos;
				if (GetAsyncKeyState(VK_RBUTTON))
				{
					float mass = 100.f;
					Vector location = vs->origin;
					Vector targetLocation(location.x, location.y + 100, location.z);
					Vector difference = location - targetLocation;
					D3DXVECTOR3 d3dDifference(difference.x, difference.y, difference.z);
					D3DXVECTOR3 normalizedDifference;
					D3DXVec3Normalize(&normalizedDifference, &d3dDifference);

					normalizedDifference *= mass;
					normalizedDifference *= 1000; // meterspersecond

					networkmanager->AskForAddImpulse(entity, new D3DXVECTOR3(normalizedDifference.x, normalizedDifference.y, normalizedDifference.z), 0);
				}
				//vs->pos = Vector(0, 0, 0);

				//test
				networkmanager->SetVisibilityMessage(entity, false);

				Camera* camera = world->GetCamera();
				if (!camera)
					continue;

				EntityTable* bullets = world->GetBullets();
				for (int i = 0; i < world->BulletsSize(); i++)
				{
					Entity* bullet_entity = bullets->GetEntityFromIndex(i);
					if (!bullet_entity)
						continue;

					EntityLink* bullet_link = bullet_entity->link;
					if (!bullet_link)
						continue;

					Object* bullet_obj = bullet_link->obj;
					if (!bullet_obj)
						continue;

					VisualState* bullet_vs = bullet_obj->GetFutureVisualState();
					if (!bullet_vs)
						continue;

					bullet_vs->origin = vs->head;

					Vector screen;
					if (camera->WorldToScreen(bullet_vs->origin, screen))
						renderer->DrawString(12, screen.x, screen.y, Color(255, 255, 255, 255), "Bullet", true);

					break;
				}

				Vector screen;
				if(camera->WorldToScreen(vs->origin, screen))
					renderer->DrawString(12, screen.x, screen.y, Color(255, 255, 255, 255), obj->GetObjectType()->type1->GetValue(), true);

				
					
				
			}
		}
	}

	renderer->FillRect(40, 40, 350, 400, Color(80, 80, 80, 150));
	renderer->DrawString(12, 42, 41, Color(255, 255, 255, 255), "Menu", true);

	renderer->EndScene();

	return original_function(swapchain, syncinterval, flags);
}

bool PresentHook::Init()
{
	world = *reinterpret_cast<World**>(reinterpret_cast<DWORD64>(GetModuleHandle(0)) + 0x2553F48);
	networkmanager = *reinterpret_cast<NetworkManager**>(reinterpret_cast<DWORD64>(GetModuleHandle(0)) + 0x2512170);
	printf(std::to_string(reinterpret_cast<DWORD64>(world)).c_str());
	if (!world)
		return false;

	EngineDD11* engine = world->GetEngine();
	if (!engine)
		return false;

	Hook* hook = new Hook(engine->swapchain, 8, &Present);
	original_function = static_cast<PresentType>(hook->ReplaceVirtual());

	return true;
}

PresentHook presenthook;