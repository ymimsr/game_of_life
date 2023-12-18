//
// Created by Ramil on 12/18/2023.
//

#include <iostream>
#include "ConsoleView.h"

void ConsoleView::PrintGameState(GameState* gameState, int iteration) {
    std::cout << "Iteration #" << iteration << std::endl;
    std::cout << "Universe name: " << gameState->GetUniverseName() << std::endl;
    bool** cells = gameState->GetCells();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < gameState->GetHeight(); y++) {
        for (int x = 0; x < gameState->GetWidth(); x++) {
            if (cells[y][x]) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                std::cout << ALIVE_CELL_STRING;
            } else {
                SetConsoleTextAttribute(hConsole, DEFAULT_PALETTE);
                std::cout << DEAD_CELL_STRING;
            }
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, DEFAULT_PALETTE);
}
