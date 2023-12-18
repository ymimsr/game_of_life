//
// Created by Ramil on 12/7/2023.
//

#include "GameState.h"

#include <utility>


const std::string &GameState::GetUniverseName() const {
    return universeName;
}

const std::vector<int> &GameState::GetBirthRate() const {
    return birthRate;
}

const std::vector<int> &GameState::GetSurvivalRate() const {
    return survivalRate;
}

GameState::GameState(std::string universeName, std::vector<int> birthRate,
                     std::vector<int> survivalRate, const int width, const int height, bool **cells)
        : universeName(std::move(universeName)), birthRate(std::move(birthRate)), survivalRate(std::move(survivalRate)), width(width), height(height),
          cells(cells) {}

int GameState::GetWidth() const {
    return width;
}

int GameState::GetHeight() const {
    return height;
}

bool **GameState::GetCells() const {
    return cells;
}
