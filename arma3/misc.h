#pragma once

class Misc
{
private:
	void ImpulseAll(Object* player);
public:
	bool Init();
	void Frame(D3D11Renderer* renderer, Object* player);
};

extern Misc misc;