//
// Created by Ramil on 12/18/2023.
//

#include "ConsoleView.h"
#include <windows.h>

void ConsoleView::PrintGameState(GameState *gameState) {
    printf("====================================\n");
    CellGrid* cellGrid = gameState->getCellGrid();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < cellGrid->getHeight(); y++) {
        for (int x = 0; x < cellGrid->getWidth(); x++) {
            if (cellGrid->GetCell(x, y).alive) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                std::cout << "O";
            } else {
                SetConsoleTextAttribute(hConsole, DEFAULT_PALETTE);
                std::cout << "O";
            }
        }
        std::cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, DEFAULT_PALETTE);
}
