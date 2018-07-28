#pragma once

typedef uintptr_t ptr;
typedef unsigned int uint;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

class Memory
{
public:
	static HMODULE WINAPI GetModuleBaseAddress(LPCWSTR moduleName);
	PIMAGE_NT_HEADERS GetNTHeader(HMODULE hmModule);

	std::string HexToBytes(std::string hex);
	ptr SigScan(const char* pattern, const char* module);
};