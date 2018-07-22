#pragma once

inline uintptr_t getvfunc(void* table, size_t index)
{
	return ((*(uintptr_t**)table)[index]);
}

template <typename T>
inline T getvfunc(void* table, size_t index)
{
	return T(getvfunc(table, index));
}
