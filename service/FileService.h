//
// Created by Ramil on 11/19/2023.
//
#include <string>
#include <regex>
#include "../model/builder/GameStateBuilder.h"

#ifndef LAB_2_FILESERVICE_H
#define LAB_2_FILESERVICE_H


class FileService {
private:
    static void ReadAndValidateHeader(std::ifstream& file, GameStateBuilder& gameStateBuilder);
    static std::vector<int> ParseStringToIntVector(char *string);
    static std::string IntVectorToString(std::vector<int> vector);
    static void ReadAliveCells(std::ifstream& file, GameStateBuilder& gameStateBuilder);
public:
    static GameState* ImportGameState(const std::string& inputFileName);
    static void ExportGameState(GameState* gameState, const std::string& outputFileName);
};


#endif //LAB_2_FILESERVICE_H
