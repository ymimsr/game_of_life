//
// Created by Ramil on 12/18/2023.
//

#include <sstream>
#include "ConsoleController.h"
#include "../view/ConsoleView.h"

ConsoleController::ConsoleController() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, DEFAULT_PALETTE);
}

void ConsoleController::Start(int argc, char **argv) {
    if (argc == 2) {
        // Running in "online" mode
        std::string argString(argv[1]);
        std::string inputFileName = argString.substr(InputArgString.size());
        StartOnlineMode(inputFileName);
        return;
    }

    std::string inputFileName;
    std::string outputFileName;
    int iterations;

    bool isInputFileNameRead = false, isOutputFileNameRead = false, isIterationsLoaded = false;
    for (int i = 1; i < argc; i++) {
        std::string argString(argv[i]);

        if (0 == argString.compare(0, InputArgString.size(), InputArgString)) {
            inputFileName = argString.substr(InputArgString.size());

            isInputFileNameRead = true;
            continue;
        }

        if (0 == argString.compare(0, OutputArgString.size(), OutputArgString)) {
            outputFileName = argString.substr(OutputArgString.size());

            isOutputFileNameRead = true;
            continue;
        }

        if (0 == argString.compare(0, IterationsArgString.size(), IterationsArgString)) {
            iterations = std::stoi(argString.substr(IterationsArgString.size()));

            isIterationsLoaded = true;
            continue;
        }
    }

    if (!isInputFileNameRead) {
        std::cout << "ERROR: Input file name is not loaded." << std::endl;
        exit(-1);
    }

    if (!isIterationsLoaded) {
        std::cout << "WARNING: More than one argument were provided. "
                     "Missing --iterations=<n> for running. "
                     "Using iterations = " << DEFAULT_ITERATIONS << std::endl;
        iterations = DEFAULT_ITERATIONS;
    }

    if (!isOutputFileNameRead) {
        std::cout << "WARNING: More than one argument were provided. "
                     "Missing --output=<filename> for running. "
                     "Using " << DEFAULT_OUTPUT_FILENAME << " as output file name." << std::endl;
        outputFileName = DEFAULT_OUTPUT_FILENAME;
    }

    StartOfflineMode(inputFileName, outputFileName, iterations);
}

void ConsoleController::StartOfflineMode(std::string inputFileName, std::string outputFileName, int iterations) {
    std::cout << "INFO: Start game in \"offline\" mode..." << std::endl;

    std::cout << "INFO: Importing game state from " << inputFileName << "..." << std::endl;
    GameState* gameState = FileService::ImportGameState(inputFileName);
    std::cout << "INFO: Successfully finished importing game state" << std::endl;

    Game* game = new Game(gameState);

    game->Tick(iterations);

    FileService::ExportGameState(gameState, outputFileName);
}

void ConsoleController::StartOnlineMode(std::string inputFileName) {
    std::cout << "INFO: Start game in \"online\" mode..." << std::endl;

    std::cout << "INFO: Importing game state from " << inputFileName << "..." << std::endl;
    GameState* gameState = FileService::ImportGameState(inputFileName);
    std::cout << "INFO: Successfully finished importing game state" << std::endl;

    Help();

    Game* game = new Game(gameState);

    std::string commandLine;
    int iterationCount = 0;
    while (true) {
        std::getline(std::cin, commandLine);

        if (0 == commandLine.compare(0, DumpCommandString.size(), DumpCommandString)) {
            std::string outputFileName = commandLine.substr(DumpCommandString.size() + 1);

            if (0 == outputFileName.compare(inputFileName.length() - 5, 5, ".life")) {
                std::cout << "ERROR: Given filename has incorrect format. Should end with .life" << std::endl;
                continue;
            }

            std::cout << "INFO: Exporting game state to file " << outputFileName << "..." << std::endl;
            FileService::ExportGameState(gameState, outputFileName);
            std::cout << "INFO: Finished exporting game state to file..." << std::endl;

            continue;
        }

        if (0 == commandLine.compare(0, TickCommandString.size(), TickCommandString)) {
            int iterations = DEFAULT_TICK_ITERATIONS;
            if (commandLine.size() > TickCommandString.size()) {
                iterations = std::stoi(commandLine.substr(TickCommandString.size() + 1));
            }

            std::cout << "INFO: Running " << iterations << " iterations..." << std::endl;
            game->Tick(iterations);
            std::cout << "INFO: Finished running " << iterations << " iterations" << std::endl;

            iterationCount += iterations;
            ConsoleView::PrintGameState(gameState, iterationCount);

            continue;
        }

        if (0 == commandLine.compare(0, AutoTickCommandString.size(), AutoTickCommandString)) {
            int iterations = DEFAULT_AUTOTICK_ITERATIONS;
            int wait_ms = DEFAULT_AUTOTICK_WAIT_MS;

            std::stringstream ss(commandLine);

            // skip first token
            std::string firstToken;
            std::string secondToken;
            std::string thirdToken;

            ss >> firstToken >> secondToken >> thirdToken;

            if (!secondToken.empty()) {
                iterations = std::stoi(secondToken);
            }

            if (!thirdToken.empty()) {
                wait_ms = std::stoi(thirdToken);
            }

            for (int i = 0; i < iterations; i++) {
                game->Tick();
                ConsoleView::PrintGameState(gameState, ++iterationCount);
                Sleep(wait_ms);
            }

        }

        if (0 == commandLine.compare(0, HelpCommandString.size(), HelpCommandString)) {
            Help();

            continue;
        }

        if (0 == commandLine.compare(0, ExitCommandString.size(), ExitCommandString)) {
            std::cout << "INFO: Exiting the game...";

            // TODO: add free and stuff...

            return;
        }

        std::cout << "ERROR: Can't recognize a command. Type \"help\" to see list of commands" << std::endl;
    }
}

void ConsoleController::Help() {
    std::cout << "Usage:" << std::endl;
    std::cout << CONSOLE_TABULATION << "dump <filename> - Exports game state to <filename>" << std::endl;
    std::cout << CONSOLE_TABULATION << "tick <n=" << DEFAULT_TICK_ITERATIONS << "> "
        << "- Calculate <n> iterations. "
        << "Prints game state to console after calculating." << std::endl;
    std::cout << CONSOLE_TABULATION << "autotick <n=" << DEFAULT_AUTOTICK_ITERATIONS << "> "
        << "<ms=" << DEFAULT_AUTOTICK_WAIT_MS << "> "
        <<"- Calculates <n> iterations and printing game state "
        << "after each iteration. Waits ms before each iteration" << std::endl;
    std::cout << CONSOLE_TABULATION << "exit - Stop game" << std::endl;
    std::cout << CONSOLE_TABULATION << "help - Show help info (this info)" << std::endl;
}
