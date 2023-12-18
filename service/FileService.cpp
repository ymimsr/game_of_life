//
// Created by Ramil on 11/19/2023.
//

#include "FileService.h"
#include <fstream>
#include <iostream>
#include <regex>

#define GAME_VERSION_LINE "#Life 1.06"

GameState* FileService::ImportGameState(const std::string& inputFileName) {
    if (0 != inputFileName.compare(inputFileName.length() - 5, 5, ".life")) {
        std::cout << "ERROR: File name has incorrect format. Should end with .life" << std::endl;
        throw std::exception("Incorrect format for input file");
    }

    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        printf("ERROR: Can't open a file");
        throw std::exception("Can't open a file");
    }

    auto* gameStateBuilder = new GameStateBuilder();

    ReadAndValidateHeader(inputFile, *gameStateBuilder);
    ReadAliveCells(inputFile, *gameStateBuilder);

    inputFile.close();

    return gameStateBuilder->Build();
}

/*
 * Header consists of four lines:
 *  Format version, mandatory. Ex.: #Life 1.06
 *  Universe name, optional. Ex.: #N My universe
 *  Transition rules, optional. Ex.: #R Bx/Ry
 *  Map size, optional. Ex.: #S Xx/Yy
 */
void FileService::ReadAndValidateHeader(std::ifstream& file, GameStateBuilder& gameStateBuilder) {
    const std::regex universeNameRegex (R"(^#N .*$)");
    const std::regex transitionRulesRegex(R"(^#R B[012345678]{0,9}\/S[0123456678]{0,9}$)");
    const std::regex sizeRegex (R"(^#S X\d+\/Y\d+$)");

    std::string line;

    std::getline(file, line);

    if (line != GAME_VERSION_LINE) {
        printf("ERROR: First line doesn't match format. Should be %s",
               GAME_VERSION_LINE);
        throw std::exception("Incorrect header format");
    }

    bool isUniverseRead = false, isTransitionRulesRead = false, isSizeConfigRead = false;
    while (true) {
        int prev_pos = file.tellg();
        std::getline(file, line);

        if (!isUniverseRead && std::regex_match(line, universeNameRegex)) {
            char universeName[100];

            sscanf(line.c_str(), "#N %99[0-9a-zA-Z ]", universeName);

            gameStateBuilder.UniverseName(universeName);

            isUniverseRead = true;
            continue;
        }

        if (!isTransitionRulesRead && std::regex_match(line, transitionRulesRegex)) {
            char birthRateCharArray[10];
            char survivalRateCharArray[10];

            sscanf(line.c_str(), "#R B%9[0-8]/S%9[0-8]",
                     birthRateCharArray,
                     survivalRateCharArray);

            gameStateBuilder.BirthRate(ParseStringToIntVector(birthRateCharArray));
            gameStateBuilder.SurvivalRate(ParseStringToIntVector(survivalRateCharArray));

            isTransitionRulesRead = true;
            continue;
        }

        if (!isSizeConfigRead && std::regex_match(line, sizeRegex)) {
            int width, height;

            sscanf(line.c_str(), "#S X%d/Y%d",
                     &width,
                     &height);

            gameStateBuilder.MaxX(width);
            gameStateBuilder.MaxY(height);

            isSizeConfigRead = true;
            continue;
        }

        file.seekg(prev_pos);
        break;
    }
}

std::vector<int> FileService::ParseStringToIntVector(char* string) {
    std::vector<int> vector;
    int stringLength = strlen(string);
    vector.reserve(stringLength);
    for (int i = 0; i < stringLength; i++) {
        vector.push_back(string[i] - '0');
    }

    return vector;
}

std::string FileService::IntVectorToString(std::vector<int> vector) {
    std::string string;
    for (int x : vector) {
        string += std::to_string(x);
    }

    return string;
}

void FileService::ReadAliveCells(std::ifstream &file, GameStateBuilder &gameStateBuilder) {
    std::string line;
    while (std::getline(file, line)) {
        int x, y;
        sscanf(line.c_str(), "%d %d",
                 &x,
                 &y);

        gameStateBuilder.AliveCell(x, y);
    }
}

void FileService::ExportGameState(GameState *gameState, const std::string& outputFileName) {
    std::ofstream outputFile;
    outputFile.open(outputFileName);

    outputFile << GAME_VERSION_LINE << "\n";
    outputFile << "#N " << gameState->GetUniverseName() << "\n";
    outputFile << "#R B"
               << IntVectorToString(gameState->GetBirthRate()) << "/S"
               << IntVectorToString(gameState->GetSurvivalRate()) << "\n";
    outputFile << "#S X"
               << gameState->GetWidth() << "/Y"
        << gameState->GetHeight();

    for (int y = 0; y < gameState->GetHeight(); y++) {
        for (int x = 0; x < gameState->GetWidth(); x++) {
            if (gameState->GetCells()[y][x]) {
                outputFile << "\n" << x << " " << y;
            }
        }
    }

    outputFile.close();
}
