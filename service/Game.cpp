//
// Created by Ramil on 12/18/2023.
//

#include "Game.h"

void Game::Tick() {
    bool** cells = gameState->GetCells();
    const std::vector<int>& birthRate = gameState->GetBirthRate();
    const std::vector<int>& survivalRate = gameState->GetSurvivalRate();

    std::vector<Cell> toAlive;
    std::vector<Cell> toKill;

    for (int y = 0; y < gameState->GetHeight(); y++) {
        for (int x = 0; x < gameState->GetWidth(); x++) {
            int aliveNeighboursCount = CountAliveNeighbours(x, y);

            if (cells[y][x]) {
                // if not present in survivalRate
                if (!(std::find(survivalRate.begin(), survivalRate.end(), aliveNeighboursCount) != survivalRate.end())) {
                    toKill.push_back(Cell {
                        .x = x,
                        .y = y
                    });
                }
            } else {
                // if present in birthRate
                if ((std::find(birthRate.begin(), birthRate.end(), aliveNeighboursCount) != birthRate.end())) {
                    toAlive.push_back(Cell {
                            .x = x,
                            .y = y
                    });
                }
            }
        }
    }

    for (Cell cell : toAlive) {
        cells[cell.y][cell.x] = true;
    }

    for (Cell cell : toKill) {
        cells[cell.y][cell.x] = false;
    }
}

Game::Game(GameState *gameState) : gameState(gameState) {}

void Game::Tick(int n) {
    for (int i = 0; i < n; i++) {
        Tick();
    }
}

int Game::CountAliveNeighbours(int x, int y) {
    int aliveNeighboursCount = 0;

    aliveNeighboursCount += GetCell(x - 1, y - 1);
    aliveNeighboursCount += GetCell(x - 1, y);
    aliveNeighboursCount += GetCell(x - 1, y + 1);
    aliveNeighboursCount += GetCell(x, y - 1);
    aliveNeighboursCount += GetCell(x, y + 1);
    aliveNeighboursCount += GetCell(x + 1, y - 1);
    aliveNeighboursCount += GetCell(x + 1, y);
    aliveNeighboursCount += GetCell(x + 1, y + 1);

    return aliveNeighboursCount;
}

bool Game::GetCell(int x, int y) {
    if (x == -1) {
        x = gameState->GetWidth() - 1;
    }

    if (x == gameState->GetWidth()) {
        x = 0;
    }

    if (y == -1) {
        y = gameState->GetHeight() - 1;
    }

    if (y == gameState->GetHeight()) {
        y = 0;
    }

    if (x < 0 || x > gameState->GetWidth() || y < 0 || y > gameState->GetHeight()) {
        printf("ERROR: Game process is trying to access cell out of bounds");
        throw std::exception("Trying to access cell out of bounds");
    }

    return gameState->GetCells()[y][x];
}


