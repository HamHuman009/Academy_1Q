#pragma once
#include "../stdafx.h"

class Ranking
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

	Ranking();
	~Ranking();

	void saveRankings();
	void loadRankings();
	void sortRank();
	void rankToStr();
};