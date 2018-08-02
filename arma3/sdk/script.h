#pragma once

struct EvalContext
{
	bool _localOnly;
	bool _undefinedIsNil;
};

class StringWrapper
{
	ArmaString* string;
public:
	StringWrapper(std::string str)
	{
		string = ArmaString::CreateArmaString(str);
	}
};

class GameState
{
private:
	
	DWORD64 GetExecuteAddy()
	{
		return DWORD64(GetModuleHandle(0)) + 0x12EF9D0;
	}
	/* 4C 89 4C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B A5 ? ? ? ? 4D 8B E8 48 8B F2 4C 8B F1 4D 85 E4 75 31 44 38 A1 ? ? ? ? 74 09 4C 8D 25 ? ? ? ?  */
public:
/*
	void Execute(const char* expression)
	{
		using fnGameStateExecute = void(__thiscall* )(void*, StringWrapper*, DWORD64);
		fnGameStateExecute GameStateExecute = fnGameStateExecute(GetExecuteAddy());
		StringWrapper* src = new StringWrapper(expression);
		DWORD64 context = (DWORD64)GetModuleHandle(0) + 0x2231F20;
		GameStateExecute(this, src, context);
		// ctx = base + 0x2231F20;
	}*/

	void Execute(const char* expression, EvalContext* ctx, uintptr_t* globals)
	{
		typedef void(__thiscall *tFunction)(GameState*, const char*, EvalContext*, uintptr_t*);
		tFunction oFunction = (tFunction)(GetModuleHandle(0) + 0x12EF9D0);
		oFunction(this, expression, ctx, globals);
	}
};

extern EvalContext* GEvalContext;

class ScriptThread
{
public:
	char pad_0x0000[0x488]; //0x0000
	ArmaString* scriptText; //0x0488 
	char pad_0x0490[0x8]; //0x0490
	ArmaString* scriptName; //0x0498 
	char pad_0x04A0[0x8]; //0x04A0
	ArmaString* sourceText; //0x04A8 
	char pad_0x04B0[0x58]; //0x04B0
	unsigned char bTerminate; //0x0508 
	char pad_0x0509[0x3F]; //0x0509

	void Terminate()
	{
		bTerminate = true;
	}

	void AppendToSource(std::string source)
	{
		std::string script_text = scriptText->GetValue() + "\n" + source;
		//scriptText->SetLength(script_text.length());
	}

}; //Size=0x0548

class VMContainer
{
public:
	ScriptThread* Thread; //0x0000 
	float lastTimeSinceExec; //0x0008 
	char pad_0x000C[0x4]; //0x000C

	void DumpData(int i)
	{
		if (Thread)
		{
			std::ofstream file;
			std::string script_name = "Script" + i;
			file.open(script_name);
			file << "Script Location: " << Thread->sourceText->GetValue() << "\n\n\n";
			file << Thread->scriptText->GetValue() << std::endl;
			file.close();
		}
	}

}; //Size=0x0010

class ScriptVM
{
public:
	VMContainer GetContainer(int idx)
	{
		return *(VMContainer*)(this + (0x10 * idx));
	}
};