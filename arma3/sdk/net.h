#pragma once

class NetworkManager
{
public:
	void AddImpulse(Object* obj, Vector* impulseVector, Vector* torque)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*, Vector*, Vector*);
		return (getvfunc<OriginalFn>(this, 191))(this, obj, impulseVector, torque);
	}

	void AskSetVisibility(Object* obj, bool b)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*, bool);
		return (getvfunc<OriginalFn>(this, 152))(this, obj, b);
	}

	void SetVisibility(Object* obj, bool b)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*, bool);
		return (getvfunc<OriginalFn>(this, 153))(this, obj, b);
	}

	void DeleteBackpack(Object* obj)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*);
		return(getvfunc<OriginalFn>(this, 261))(this, obj);
	}

	void GetOut(Object* obj, Object* vehicle, Object* turret, bool eject, bool parachute)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*, Object*, Object*, bool, bool);
		return(getvfunc<OriginalFn>(this, 168))(this, obj, vehicle, turret, eject, parachute);
	}
};