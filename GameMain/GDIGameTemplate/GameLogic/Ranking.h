#pragma once
#include "../stdafx.h"

class Ranking
{

public:
	struct r_Player {
		std::string name;
		int score;

		r_Player(const std::string& n, int s) :name(n), score(s) {}
	};

	std::vector<r_Player> players;
	//std::string filename;
	std::wstring filename;

	std::string str_rank;

	Ranking();
	~Ranking();
	int InRankPlayer(UINT score);
	void saveRankings();
	void loadRankings();
	void sortRank();
	void rankToStr();
};