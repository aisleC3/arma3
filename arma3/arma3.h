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
#include <bemapiset.h>
#include <intrin.h>

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

class Vector
{
public:
	Vector() : x(0), y(0), z(0) {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}

	float x, y, z;

	bool operator == (const Vector& v) const { return v.x == x && v.y == y && v.z == z; }
	bool operator != (const Vector& v) const { return v.x != x || v.y != y || v.z != z; }

	inline Vector operator-(const Vector& v) { return Vector(x - v.x, y - v.y, z - v.z); }

	inline float Dot(Vector a) { return x * a.x + y * a.y + z * a.z; }
};

// core
#include "vmt.h"
#include "memory.h"

// sdk
#include "sdk\ui.h"
#include "sdk\event.h"
#include "sdk\weapon.h"
#include "sdk\entity.h"
#include "sdk\camera.h"
#include "sdk\script.h"
#include "sdk\world.h"
#include "sdk\net.h"

// cheat
#include "interfaces.h"
#include "entities.h"
#include "aimbot.h"
#include "esp.h"
#include "misc.h"
#include "presenthook.h"