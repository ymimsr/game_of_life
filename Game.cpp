//
// Created by Ramil on 12/18/2023.
//

#include "Game.h"

void Game::Tick(GameState* gameState) {
    CellGrid* cellGrid = gameState->getCellGrid();
    std::vector<int> birthRate = gameState->getBirthRate();
    std::vector<int> survivalRate = gameState->getSurvivalRate();

    std::vector<Cell> toAlive;
    std::vector<Cell> toKill;

    for (int y = 0; y < cellGrid->getHeight(); y++) {
        for (int x = 0; x < cellGrid->getWidth(); x++) {
            int aliveCellsAmount = 0;

            aliveCellsAmount += cellGrid->GetCell(x - 1, y - 1).alive;
            aliveCellsAmount += cellGrid->GetCell(x - 1, y).alive;
            aliveCellsAmount += cellGrid->GetCell(x - 1, y + 1).alive;
            aliveCellsAmount += cellGrid->GetCell(x, y - 1).alive;
            aliveCellsAmount += cellGrid->GetCell(x, y + 1).alive;
            aliveCellsAmount += cellGrid->GetCell(x + 1, y - 1).alive;
            aliveCellsAmount += cellGrid->GetCell(x + 1, y).alive;
            aliveCellsAmount += cellGrid->GetCell(x + 1, y + 1).alive;

            if (cellGrid->GetCell(x, y).alive) {
                if (!(std::find(survivalRate.begin(), survivalRate.end(), aliveCellsAmount) != survivalRate.end())) {
                    toKill.push_back(Cell {
                        .x = x,
                        .y = y
                    });
                }
            } else {
                if ((std::find(birthRate.begin(), birthRate.end(), aliveCellsAmount) != birthRate.end())) {
                    toAlive.push_back(Cell {
                            .x = x,
                            .y = y
                    });
                }
            }
        }
    }

    for (Cell cell : toAlive) {
        cellGrid->AliveCell(cell.x, cell.y);
    }

    for (Cell cell : toKill) {
        cellGrid->KillCell(cell.x, cell.y);
    }
}
