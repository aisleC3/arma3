#pragma once

class World
{
public:
	EngineDD11* GetEngine()
	{
		return *(EngineDD11**)(this + 0x458);
	}

	Camera* GetCamera()
	{
		return *(Camera**)(this + 0x7D8);
	}

	uintptr_t* GetGameDataNamespace()
	{
		return *(uintptr_t**)(this + 0x11F0);
	}

	ScriptVM* GetScriptVM()
	{
		return *(ScriptVM**)(this + 0x1400);
	}

	int GetThreadsNum()
	{
		return *(int*)(this + 0x1408);
	}

	int GetMaxThreadsNum()
	{
		return *(int*)(this + 0x1410);
	}

	EntityTable* GetBullets()
	{
		return *(EntityTable**)(this + 0x15E0);
	}

	int BulletsSize()
	{
		return *(int*)(this + 0x15E8);
	}

	EntityTable* GetNearEnts()
	{
		return *(EntityTable**)(this + 0x16B0);
	}

	int NearEntsSize()
	{
		return *(int*)(this + 0x16B8);
	}

	EntityTable* GetFarEnts()
	{
		return *(EntityTable**)(this + 0x1778);
	}

	int FarEntsSize()
	{
		return *(int*)(this + 0x1780);
	}

	EntityLink* GetlocalPlayer()
	{
		return *(EntityLink**)(this + 0x26D8);
	}
};