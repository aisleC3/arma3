#pragma once

class Entities
{
private:
	std::vector<Object*> players;

public:

	std::vector<Object*> GetPlayers();

	bool Init();
	void StoreEntities();
	void ClearEntities();
};

extern Entities entities;