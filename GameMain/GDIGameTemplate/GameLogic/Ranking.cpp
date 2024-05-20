#include "Ranking.h"

Ranking::Ranking() {
    filename = L"rankings.txt";
    loadRankings();
    sortRank();
    rankToStr();
}

bool comparePlayer(const Ranking::r_Player& p1, const Ranking::r_Player& p2)
{
    return p1.score > p2.score;
}

void Ranking::saveRankings()
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }
    int rank = 1;
    for (const r_Player& player : players) {
        file << player.name << " " << player.score << std::endl;
        rank++;
        if (rank == 10)
        {
            break;
        }
    }

    file.close();
}

void Ranking::loadRankings()
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }

    std::string name;
    int score;
    int rank = 1;
    while (file >> name >> score) {
        players.push_back(r_Player(name, score));
        rank++;
        if (rank == 10)
        {
            break;
        }
    }

    file.close();
}

void Ranking::sortRank()
{
    std::sort(players.begin(), players.end(), comparePlayer);
}

void Ranking::rankToStr()
{
    str_rank = "";
    int rank = 1;

    for (const r_Player& player : players) {
        str_rank += "   " + std::to_string(rank)  + "." + player.name + " - " + std::to_string(player.score) + "\n";
        rank++;
        if (rank == 10)
        {
            break;
        }
    }
}

int Ranking::InRenkPlayer(UINT score)
{
    r_Player tmpP = { "temp" ,(int)score };
    int rank = 1;
    for (const r_Player& player : players) {
        if (comparePlayer(tmpP, player)) {
            break;
        }
        rank++;
    }
    return rank;
}

Ranking::~Ranking() {

}