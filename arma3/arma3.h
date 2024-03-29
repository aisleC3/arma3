#pragma once

// win
#include <Windows.h>
#include <winternl.h>
#include <Xinput.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <comdef.h>
#include <minwindef.h>
#include <winbase.h>
#include <intrin.h>
#include <psapi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx10.lib")

// stl
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <sstream>

// lib
#include "dx11renderer\D3D11Renderer.h"

// core
#include "vmt.h"
#include "memory.h"

// sdk
#include "sdk\vector.h"
#include "sdk\ui.h"
#include "sdk\event.h"
#include "sdk\weapon.h"
#include "sdk\entity.h"
#include "sdk\camera.h"
#include "sdk\script.h"
#include "sdk\world.h"
#include "sdk\network.h"

// cheat
#include "interfaces.h"
#include "entities.h"
#include "aimbot.h"
#include "esp.h"
#include "misc.h"
#include "presenthook.h"