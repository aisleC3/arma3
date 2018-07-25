#pragma once

struct EvalContext
{
	bool _localOnly;
	bool _undefinedIsNil;
};

class GameState
{
public:
	void Execute(const char* expression, uintptr_t* globals)
	{

	}
};

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