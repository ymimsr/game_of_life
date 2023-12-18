//
// Created by Ramil on 12/7/2023.
//

#include "GameState.h"

#include <utility>

GameState::GameState(std::string universeName, std::vector<int> birthRate,
                     std::vector<int> survivalRate, CellGrid *cellGrid) : universeName(std::move(universeName)),
                                                                                 birthRate(std::move(birthRate)),
                                                                                 survivalRate(std::move(survivalRate)),
                                                                                 cellGrid(cellGrid) {}

const std::string &GameState::getUniverseName() const {
    return universeName;
}

const std::vector<int> &GameState::getBirthRate() const {
    return birthRate;
}

const std::vector<int> &GameState::getSurvivalRate() const {
    return survivalRate;
}

CellGrid *GameState::getCellGrid() const {
    return cellGrid;
}