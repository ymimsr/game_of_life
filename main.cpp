#include <iostream>
#include "FileService.h"
#include "Game.h"
#include "ConsoleView.h"

int main() {
    GameState* gameState = FileService::ImportGameState("test1.life");
    ConsoleView::PrintGameState(gameState);
    Game::Tick(gameState);
    ConsoleView::PrintGameState(gameState);
    Game::Tick(gameState);
    ConsoleView::PrintGameState(gameState);
    Game::Tick(gameState);
    ConsoleView::PrintGameState(gameState);
    Game::Tick(gameState);
    ConsoleView::PrintGameState(gameState);
    FileService::ExportGameState(gameState);
    printf("%d", gameState->getCellGrid()->GetCell(1, 2).x);
    return 0;
}
