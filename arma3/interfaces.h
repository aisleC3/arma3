#pragma once

class Interfaces
{
public:
	World* world;
	NetworkManager* network_manager;

	bool Init();
};

extern Interfaces ints;