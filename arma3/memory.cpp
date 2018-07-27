#include "arma3.h"

/* This is probably the only thing I'll use C-Style casting for, you win this time kila */

HMODULE WINAPI Memory::GetModuleBaseAddress(LPCWSTR moduleName)
{
	PEB *pPeb = NULL;
	LIST_ENTRY *pListEntry = NULL;
	LDR_DATA_TABLE_ENTRY *pLdrDataTableEntry = NULL;

	pPeb = (PPEB)__readgsqword(0x60);

	if (pPeb == NULL)
		return NULL;

	pLdrDataTableEntry = (PLDR_DATA_TABLE_ENTRY)pPeb->Ldr->InMemoryOrderModuleList.Flink;
	pListEntry = pPeb->Ldr->InMemoryOrderModuleList.Flink;

	do
	{
		if (lstrcmpiW(pLdrDataTableEntry->FullDllName.Buffer, moduleName) == 0)
			return (HMODULE)pLdrDataTableEntry->Reserved2[0];

		pListEntry = pListEntry->Flink;
		pLdrDataTableEntry = (PLDR_DATA_TABLE_ENTRY)(pListEntry->Flink);

	} while (pListEntry != pPeb->Ldr->InMemoryOrderModuleList.Flink);

	return NULL;
}

PIMAGE_NT_HEADERS Memory::GetNTHeader(HMODULE hmModule)
{
	if (hmModule == nullptr)
		return nullptr;

	IMAGE_DOS_HEADER* pDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(hmModule);

	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return nullptr;

	PIMAGE_NT_HEADERS pNtHeader = make_ptr< PIMAGE_NT_HEADERS >(hmModule, pDosHeader->e_lfanew);

	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return nullptr;

	return pNtHeader;
}


//Example Usage
/*
offset_DrawHud = FindPattern::Find("40 55 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 01");//Function Example

DWORD64 dwUEngine = FindPattern::Find("48 8B 05 ? ? ? ? 48 8B 40 30 C3");//Pointer Example
unreal_UEngine = dwUEngine + *(DWORD*)(dwUEngine + 3) + 7;

DWORD64 dwGetBoneMatrix = FindPattern::Find("E8 ? ? ? ? F3 0F 10 57 ? 48 8D 54 24 ? 48 8D 4C 24 ? E8 ? ? ? ? F3 0F 10 57 ?");//Call Example
unreal_GetBoneMatrix = dwGetBoneMatrix + *(DWORD*)(dwGetBoneMatrix + 1) + 5;*/


//Get Module Size and Base
//dwImageBase = (DWORD64)OFFSETS::GetModuleBaseAddress(L"YourExeName.exe");

/*
PIMAGE_NT_HEADERS nthdr = OFFSETS::GetNTHeader(OFFSETS::GetModuleBaseAddress(L"YourExeName.exe"));
if (nthdr == nullptr)
return false;

dwImageSize = (DWORD64)nthdr->OptionalHeader.SizeOfImage;*/


//FindPattern Functions
struct GetPatternByte
{
	GetPatternByte() : ignore(true)
	{
	}

	GetPatternByte(std::string byteString, bool ignoreThis = false) {
		data = StringToUint8(byteString);
		ignore = ignoreThis;
	}

	bool ignore;
	UINT8 data;

private:
	UINT8 StringToUint8(std::string str)
	{
		std::istringstream iss(str);

		UINT32 ret;

		if (iss >> std::hex >> ret)
		{
			return (UINT8)ret;
		}

		return 0;
	}
};

struct FindPattern
{
	static DWORD64 Find(DWORD64 dwStart, DWORD64 dwLength, std::string s) {
		std::vector<GetPatternByte> p;
		std::istringstream iss(s);
		std::string w;

		while (iss >> w)
		{
			if (w.data()[0] == '?')
			{
				p.push_back(GetPatternByte());
			}
			else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
				p.push_back(GetPatternByte(w));
			}
			else
			{
				return NULL;
			}
		}

		for (DWORD64 i = 0; i < dwLength; i++)
		{
			UINT8* lpCurrentByte = (UINT8*)(dwStart + i);

			bool found = true;

			for (size_t ps = 0; ps < p.size(); ps++)
			{
				if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data) {
					found = false;
					break;
				}
			}

			if (found)
			{
				return (DWORD64)lpCurrentByte;
			}
		}

		return NULL;
	}
/*

	static DWORD64 Find(std::string s)
	{
		return Find((DWORD64)dwImageBase, (DWORD64)dwImageSize, s);
	}*/
};