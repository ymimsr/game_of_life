cmake_minimum_required(VERSION 3.17)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_2 main.cpp service/FileService.cpp service/FileService.h model/GameState.cpp model/GameState.h model/builder/GameStateBuilder.cpp model/builder/GameStateBuilder.h view/ConsoleView.cpp view/ConsoleView.h service/Game.cpp service/Game.h controller/ConsoleController.cpp controller/ConsoleController.h)