#pragma once

class Interfaces
{
public:
	World* world;
	NetworkManager* network_manager;
	GameState* game_state;

	bool Init();
};

extern Interfaces ints;