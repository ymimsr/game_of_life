cmake_minimum_required(VERSION 3.17)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_2 main.cpp FileService.cpp FileService.h gamestate/GameState.cpp gamestate/GameState.h gamestate/GameStateBuilder.cpp gamestate/GameStateBuilder.h gamestate/CellGrid.cpp gamestate/CellGrid.h ConsoleView.cpp ConsoleView.h Game.cpp Game.h)