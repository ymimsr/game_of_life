//
// Created by Ramil on 12/18/2023.
//

#ifndef LAB_2_GAME_H
#define LAB_2_GAME_H

#include "../model/GameState.h"

class Game {
private:
    GameState* gameState;
    int CountAliveNeighbours(int x, int y);
    bool GetCell(int x, int y);
public:
    Game(GameState *gameState);
    void Tick();
    void Tick(int n);
};


#endif //LAB_2_GAME_H
