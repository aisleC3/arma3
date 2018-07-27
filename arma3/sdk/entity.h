#pragma once

class VisualState
{
public:
	char pad_0000[32]; //0x0000
	Vector direction; //0x0020
	Vector origin; //0x002C
	char pad_0038[304]; //0x0038
	Vector head; //0x0168
	Vector torso; //0x0174
	char pad_0180[208]; //0x0180
}; //Size: 0x0250

class ObjectType
{
public:
	char pad_0000[4512]; //0x0000
	class ArmaString* type1; //0x11A0
	class ArmaString* type2; //0x11A8
	class ArmaString* type3; //0x11B0
	class ArmaString* type4; //0x11B8
	char pad_11C0[128]; //0x11C0
}; //Size: 0x1240

class EntityLink;
class Object
{
public:

	void SetDamage(bool a2, float var, float a4)
	{
		DWORD64 function_offset = (DWORD64)GetModuleHandle(0) + 0xB70500;
		typedef void(__thiscall* OriginalFn)(void*, bool, float, float);
		OriginalFn Func = (OriginalFn)function_offset;
		Func(this, a2, var, a4);
	}

	VisualState* GetFutureVisualState()
	{
		return *(VisualState**)(this + 0xD0);
	}

	float GetVisualHealth()
	{
		if(*(int*)(this + 0xF0))
		{
			return **(float**)(this + 0xF0);
		}
		return NULL;
	}

	void SetVisualHealth(float f) // 0 - 1
	{
		if (GetVisualHealth())
			**(float**)(this + 0xF0) = f;
	}

	ObjectType* GetObjectType()
	{
		return *(ObjectType**)(this + 0x150);
	}

	VisualState* GetRenderVisualState()
	{
		return *(VisualState**)(this + 0x190);
	}

	bool GetAllowDamage()
	{
		return *(bool*)(this + 0x1CC);
	}

	void SetAllowDamage(bool b)
	{
		*(bool*)(this + 0x1CC) = b;
	}



	EntityLink* GetParent()
	{
		return *(EntityLink**)(this + 0x4D8);
	}

	bool IsDead()
	{
		return *(bool*)(this + 0x504);
	}

	EventHandler* GetEventHandler()
	{
		return *(EventHandler**)(this + 0x608);
	}

	int GetNumEvents()
	{
		return *(int*)(this + 0x610);
	}

	bool GetNetID()
	{
		return *(int*)(this + 0xB94);
	}

	WeaponTable* GetWeaponTable()
	{
		return *(WeaponTable**)(this + 0xCD8);
	}

	float GetUnitRecoilCoefficient()
	{
		return *(float*)(this + 0x1058);
	}

	void SetUnitRecoilCoefficient(float f)
	{
		*(float*)(this + 0x1058) = f;
	}

	bool GetEnableFatigue()
	{
		return *(bool*)(this + 0x109C);
	}

	void SetEnableFatigue(bool b)
	{
		*(bool*)(this + 0x109C) = b;
	}

	float GetCustomAimCoef()
	{
		return *(float*)(this + 0x10B0);
	}

	void SetCustomAimCoef(float f)
	{
		*(float*)(this + 0x10B0) = f;
	}

	float GetAnimSpeedCoef()
	{
		return *(float*)(this + 0x2358);
	}

	void SetAnimSpeedCoef(float f)
	{
		*(float*)(this + 0x2358) = f; // 1 = default
	}

};

class EntityLink
{
public:
	char pad[0x8];
	Object* obj;
};

class Entity
{
public:
	char pad[0x10];
	EntityLink* link;

	void SetFreeze(bool freeze)
	{
		(*(bool*)(this + 0x348)) = freeze;
	}
};

class EntityTable
{
public:
	Entity* GetEntityFromIndex(int index)
	{
		return *(Entity**)(this + (index * 0x8));
	}
};