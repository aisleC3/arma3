#pragma once

#include <windows.h>

class Hook
{
private:
	void** table;
	unsigned int index;
	void* new_function;
	void* original_function;
public:
	Hook(void* object, unsigned int i, void* function) : index(i), table(*(void***)object), new_function(function) {}

	void* ReplaceVirtual()
	{
		DWORD original_protect;

		void* function = &table[index];
		VirtualProtect(function, sizeof(function), PAGE_READWRITE, &original_protect);

		original_function = table[index];
		table[index] = new_function;

		VirtualProtect(&table[index], sizeof(function), original_protect, NULL);

		return original_function;
	}
	void RevertVirtual()
	{
		DWORD original_protect;

		void* function = &table[index];
		VirtualProtect(function, sizeof(function), PAGE_READWRITE, &original_protect);

		table[index] = original_function;

		VirtualProtect(&table[index], sizeof(function), original_protect, NULL);
	}
};
