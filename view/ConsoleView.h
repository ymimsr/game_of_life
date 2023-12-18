//
// Created by Ramil on 12/18/2023.
//

#ifndef LAB_2_CONSOLEVIEW_H
#define LAB_2_CONSOLEVIEW_H


#include "../model/GameState.h"
#include <windows.h>

#define ALIVE_CELL_STRING " O "
#define DEAD_CELL_STRING " . "

class ConsoleView {
public:
    static void PrintGameState(GameState* gameState, int iteration);
};


#endif //LAB_2_CONSOLEVIEW_H
