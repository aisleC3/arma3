#pragma once

class Magazine
{
public:

	int GetAmmo()
	{
		typedef int(__thiscall* OriginalFn)(void*);
		return (getvfunc<OriginalFn>(this, 27))(this);
	}

	void SetAmmo(int ammount)
	{
		DWORD64 garbage1, garbage2;
		garbage1 = (ammount ^ 0xBABAC8B6) >> 1;
		garbage2 = (ammount & 0xBABAC8B6) - garbage1;
		*(int*)(this + 0x88) = garbage1;
		*(int*)(this + 0x94) = garbage2;
	}

	std::string GetName()
	{
		ArmaString* str = *(ArmaString**)(this + 0x50);
		return str->GetValue();
	}
};

class Weapon
{
public:
	std::string GetName()
	{
		ArmaString* str = *(ArmaString**)(this + 0x30);
		return str->GetValue();
	}
};

class WeaponTable
{
public:
	Weapon* GetWeaponInHands()
	{
		return *(Weapon**)(this + 0x8);
	}

	Magazine* GetCurrentMagaine()
	{
		DWORD64* muzzle = *(DWORD64**)(this + 0x68);
		return *(Magazine**)(muzzle + 0x48);
	}
};