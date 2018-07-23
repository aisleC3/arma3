#pragma once

class Entities
{
private:
	std::vector<Object*> players;
	std::vector<Object*> vehicles;

public:

	std::vector<Object*> GetPlayers();
	std::vector<Object*> GetVehicles();

	bool Init();
	void StoreEntities();
	void ClearEntities();
};

extern Entities entities;