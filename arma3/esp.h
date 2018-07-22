#pragma once

class ESP
{
public:
	bool Init();
	void Frame(D3D11Renderer* renderer, Object* player);
};

extern ESP esp;