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