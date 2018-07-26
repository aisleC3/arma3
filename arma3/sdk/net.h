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
		return(getvfunc<OriginalFn>(this, 262))(this, obj);
	}
};