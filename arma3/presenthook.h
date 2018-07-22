#pragma once

#include "arma3.h"

#include "hook.h"

#include "dx11renderer\D3D11Renderer.h"
#pragma warning( disable : 4244 )

class PresentHook
{
public:
	bool Init();
};

extern PresentHook presenthook;