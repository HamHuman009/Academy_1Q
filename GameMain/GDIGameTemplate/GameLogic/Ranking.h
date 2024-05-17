#pragma once
#include "../stdafx.h"

class Renking
{
	
public:
	struct Player {
		std::string name;
		int score;

		Player(const std::string& n, int s) :name(n), score(s) {}
	};

	std::vector<Player> players;
	//std::string filename;
	std::wstring filename;

	std::string str_rank;

	Renking();
	~Renking();
	
	void saveRankings();
	void loadRankings();
	void sortRank();
	void rankToStr();
};

