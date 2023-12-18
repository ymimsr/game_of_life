//
// Created by Ramil on 12/7/2023.
//

#ifndef LAB_2_GAMESTATE_H
#define LAB_2_GAMESTATE_H


#include <string>
#include <vector>
#include "CellGrid.h"

class GameState {
private:
    const std::string universeName;
    const std::vector<int> birthRate;
    const std::vector<int> survivalRate;
    CellGrid* cellGrid;
    bool** cells[];
public:
    GameState(std::string universeName, std::vector<int> birthRate, std::vector<int> survivalRate,
              CellGrid *cellGrid);

    const std::string &getUniverseName() const;

    const std::vector<int> &getBirthRate() const;

    const std::vector<int> &getSurvivalRate() const;

    CellGrid *getCellGrid() const;
};


#endif //LAB_2_GAMESTATE_H
