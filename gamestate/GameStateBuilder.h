//
// Created by Ramil on 12/7/2023.
//

#ifndef LAB_2_GAMESTATEBUILDER_H
#define LAB_2_GAMESTATEBUILDER_H


#include "GameState.h"

class GameStateBuilder {
private:
    std::string universeName = std::string();
    std::vector<int> birthRate = std::vector<int>();
    std::vector<int> survivalRate = std::vector<int>();
    int width = 0;
    int height = 0;
    std::vector<Cell> aliveCells = std::vector<Cell>();
public:
    GameStateBuilder &UniverseName(std::string universeName);
    GameStateBuilder &BirthRate(std::vector<int> birthRate);
    GameStateBuilder &SurvivalRate(std::vector<int> survivalRate);
    GameStateBuilder &MaxX(int maxX);
    GameStateBuilder &MaxY(int maxY);
    GameStateBuilder &AliveCell(int x, int y);
    GameState *Build();
private:
    void ValidateUniverseName();
    void ValidateBirthRate();
    void ValidateSurvivalRate();
    void ValidateSize();
    void ValidateAndMoveCells();
    void MoveCellsExcludingNegativeCoordinates();
    bool IsSizeSet() const;
    CellGrid *BuildCellGrid();
};


#endif //LAB_2_GAMESTATEBUILDER_H
