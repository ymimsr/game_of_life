//
// Created by Ramil on 12/7/2023.
//

#include "GameStateBuilder.h"

#include <utility>
#include <iostream>

#define DEFAULT_OFFSET_FOR_MAP_SIZE 5;
#define DEFAULT_UNIVERSE_NAME "My Universe"

GameStateBuilder &GameStateBuilder::UniverseName(std::string universeName) {
    GameStateBuilder::universeName = std::move(universeName);
    return *this;
}

GameStateBuilder &GameStateBuilder::BirthRate(std::vector<int> birthRate) {
    GameStateBuilder::birthRate = std::move(birthRate);
    return *this;
}

GameStateBuilder &GameStateBuilder::SurvivalRate(std::vector<int> survivalRate) {
    GameStateBuilder::survivalRate = std::move(survivalRate);
    return *this;
}

GameStateBuilder &GameStateBuilder::MaxX(int maxX) {
    GameStateBuilder::width = maxX;
    return *this;
}

GameStateBuilder &GameStateBuilder::MaxY(int maxY) {
    GameStateBuilder::height = maxY;
    return *this;
}

GameStateBuilder &GameStateBuilder::AliveCell(int x, int y) {
    aliveCells.push_back(Cell {
            .x = x,
            .y = y
    });
    return *this;
}

GameState* GameStateBuilder::Build() {
    ValidateUniverseName();
    ValidateBirthRate();
    ValidateSurvivalRate();
    ValidateAndMoveCells();
    // ValidateSize() should be called after ValidateAndMoveCells because it depends on alive cellGrid
    ValidateSize();

    bool** cells = BuildCells();

    auto* gameState = new GameState(
            universeName,
            birthRate,
            survivalRate,
            width,
            height,
            cells);

    return gameState;
}

bool **GameStateBuilder::BuildCells() {
    bool** cells = new bool*[height];
    for (int y = 0; y < height; y++) {
        cells[y] = new bool[width];
        for (int x = 0; x < width; x++) {
            cells[y][x] = false;
        }
    }

    for (Cell cell : aliveCells) {
        if (cells[cell.y][cell.x]) {
            printf("WARNING: Found duplicate cell, proceed to ignore it");
            continue;
        }
        cells[cell.y][cell.x] = true;
    }

    return cells;
}

// 1. check if aliveCells are empty
// 2. get rid of negative coordinate by moving aliveCells
// 3. check if aliveCells are in bounds of the given (if given) size
void GameStateBuilder::ValidateAndMoveCells() {
    if (aliveCells.empty()) {
        printf("ERROR: No alive aliveCells were given");
        throw std::exception("Cells vector is empty");
    }

    MoveCellsExcludingNegativeCoordinates();

    if (IsSizeSet()) {
        for (Cell cell : aliveCells) {
            if (cell.x >= width) {
                printf("ERROR: Cell with x: %d is out of bounds of the map, width is set to %d",
                       cell.x,
                       width);
                throw std::exception("Cell x is out of bounds");
            }

            if (cell.y >= height) {
                printf("ERROR: Cell with y: %d is out of bounds of the map, height is set to %d",
                       cell.y,
                       height);
                throw std::exception("Cell y is out of bounds");
            }
        }
    }
}

bool GameStateBuilder::IsSizeSet() const {
    return width != 0 && height != 0;
}

void GameStateBuilder::MoveCellsExcludingNegativeCoordinates() {
    // looking for the most negative X and Y for moving all aliveCells
    // to avoid negative X or Y
    int offsetX = 0, offsetY = 0;
    for (Cell cell : aliveCells) {
        if (cell.x < 0 && cell.x < offsetX) {
            offsetX = cell.x;
        }

        if (cell.y < 0 && cell.y < offsetY) {
            offsetY = cell.y;
        }
    }

    offsetX *= -1;
    offsetY *= -1;

    // moving all aliveCells
    for (Cell cell : aliveCells) {
        cell.x += offsetX;
        cell.y += offsetY;
    }
}

void GameStateBuilder::ValidateUniverseName() {
    if (universeName.empty()) {
        printf("WARNING: Universe name wasn't explicitly set. Using name %s",
               DEFAULT_UNIVERSE_NAME);
        universeName = DEFAULT_UNIVERSE_NAME;
    }
}

void GameStateBuilder::ValidateBirthRate() {
    if (birthRate.empty()) {
        printf("ERROR: birth rate configuration is missing");
        throw std::exception("Birth rate config is empty");
    }
}

void GameStateBuilder::ValidateSurvivalRate() {
    if (survivalRate.empty()) {
        if (birthRate.empty()) {
            printf("ERROR: survival rate configuration is missing");
            throw std::exception("Survival rate config is empty");
        }
    }
}

void GameStateBuilder::ValidateSize() {
    // if size is not set, then set it to
    // width + DEFAULT_OFFSET_FOR_MAP_SIZE
    // height + DEFAULT_OFFSET_FOR_MAP_SIZE
    if (!IsSizeSet()) {
        std::cout << "WARNING: Width and height were not explicitly set. "
               "Generating width and height based on alive cells" << std::endl;

        int maxCellX = 0, maxCellY = 0;
        for (Cell cell : aliveCells) {
            if (cell.x > maxCellX) {
                maxCellX = cell.x;
            }

            if (cell.y > maxCellY) {
                maxCellY = cell.y;
            }
        }

        width = maxCellX + DEFAULT_OFFSET_FOR_MAP_SIZE;
        height = maxCellY + DEFAULT_OFFSET_FOR_MAP_SIZE;
    }
}








