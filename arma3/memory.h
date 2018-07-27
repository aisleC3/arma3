#pragma once
#include <bemapiset.h>

template< typename Ty > Ty make_ptr(void* ptr, DWORD_PTR offset)
{
	return reinterpret_cast<Ty>(reinterpret_cast<DWORD_PTR> (ptr) + offset);
}

class Memory
{
public:
	static HMODULE WINAPI GetModuleBaseAddress(LPCWSTR moduleName);
	PIMAGE_NT_HEADERS GetNTHeader(HMODULE hmModule);
};

// All info is taken from https://www.nirsoft.net/kernel_struct