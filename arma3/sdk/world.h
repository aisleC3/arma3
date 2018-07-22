#pragma once

class World
{
public:
	EngineDD11* GetEngine()
	{
		return *(EngineDD11**)(this + 0x470);
	}

	Camera* GetCamera()
	{
		return *(Camera**)(this + 0x7E0);
	}

	EntityTable* GetBullets()
	{
		return *(EntityTable**)(this + 0x15E8);
	}

	int BulletsSize()
	{
		return *(int*)(this + 0x15F0);
	}

	EntityTable* GetNearEnts()
	{
		return *(EntityTable**)(this + 0x16B8);
	}

	int NearEntsSize()
	{
		return *(int*)(this + 0x16C0);
	}

	EntityLink* GetlocalPlayer()
	{
		return *(EntityLink**)(this + 0x26A8);
	}
};