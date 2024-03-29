#pragma once

class ArmaString
{
public:
	uint64_t m_referenceCount;
	uint64_t m_length;
	char m_pBuffer[1];

	std::string GetValue()
	{
		if (!this || !m_pBuffer || m_length < 1)
			return "";

		return (const char*)m_pBuffer;
	}

	static ArmaString* CreateArmaString(std::string text)
	{
		if (text.empty())
			return nullptr;

		const char* str = text.c_str();

		int length = strlen(str);
		ArmaString* armastring = (ArmaString*)malloc(length + 0xC);
		if (!armastring)
			return nullptr;

		armastring->m_referenceCount = 1;
		armastring->m_length = length;
		memcpy(&armastring->m_pBuffer, str, length + 1);

		return armastring;
	}
};

class ScoreBoard
{
public:
};

class EngineDD11
{
public:
	char pad_0000[196]; //0x0000
	int32_t width; //0x00C4
	int32_t height; //0x00C8
	char pad_00CC[2820]; //0x00CC
	class device* device; //0x0BD0
	class context* context; //0x0BD8
	class swapchain* swapchain; //0x0BE0
	char pad_0BE8[1448]; //0x0BE8
}; //Size: 0x1190
