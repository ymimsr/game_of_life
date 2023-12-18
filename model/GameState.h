//
// Created by Ramil on 12/7/2023.
//

#ifndef LAB_2_GAMESTATE_H
#define LAB_2_GAMESTATE_H


#include <string>
#include <vector>

struct Cell {
    int x = 0;
    int y = 0;
};

class GameState {
private:
    const std::string universeName;
    const std::vector<int> birthRate;
    const std::vector<int> survivalRate;
    const int width;
    const int height;
    bool** cells;
public:
    GameState(std::string universeName, std::vector<int> birthRate, std::vector<int> survivalRate,
              int width, int height, bool **cells);
    const std::string &GetUniverseName() const;
    const std::vector<int> &GetBirthRate() const;
    const std::vector<int> &GetSurvivalRate() const;
    int GetWidth() const;
    int GetHeight() const;
    bool **GetCells() const;
};


#endif //LAB_2_GAMESTATE_H
