#pragma once

class Aimbot
{
public:
	bool Init();
	void Frame(D3D11Renderer* renderer, Object* player);
};

extern Aimbot aimbot;