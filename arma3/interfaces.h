#pragma once

class Interfaces
{
private:
	DWORD64 game_base;
public:
	World* world;
	NetworkManager* network_manager;
	GameState* game_state;

	bool Init();
};

extern Interfaces ints;