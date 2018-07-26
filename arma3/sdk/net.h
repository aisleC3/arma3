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

	void GetOut(Object* obj, __int64 a3, __int64 a4, bool a5, bool a6)
	{
		typedef void(__thiscall* OriginalFn)(void*, Object*, __int64, __int64, bool, bool);
		return(getvfunc<OriginalFn>(this, 168))(this, obj, a3, a4, a5, a6);
	}
};