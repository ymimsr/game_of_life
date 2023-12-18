//
// Created by Ramil on 12/18/2023.
//

#ifndef LAB_2_CONSOLECONTROLLER_H
#define LAB_2_CONSOLECONTROLLER_H


#include <string>
#include <iostream>
#include <cstdlib>
#include "../service/FileService.h"
#include "../service/Game.h"

#define CONSOLE_TABULATION "   "
#define DEFAULT_ITERATIONS 1
#define DEFAULT_OUTPUT_FILENAME "my_output.life"

#define DEFAULT_AUTOTICK_ITERATIONS 100
#define DEFAULT_TICK_ITERATIONS 1
#define DEFAULT_AUTOTICK_WAIT_MS 500

class ConsoleController {
private:
    static inline const auto InputArgString = std::string("--input=");
    static inline const auto OutputArgString = std::string("--output=");
    static inline const auto IterationsArgString = std::string("--iterations=");

    static inline const auto DumpCommandString = std::string("dump");
    static inline const auto TickCommandString = std::string("tick");
    static inline const auto AutoTickCommandString = std::string("autotick");
    static inline const auto HelpCommandString = std::string("help");
    static inline const auto ExitCommandString = std::string("exit");

    void StartOfflineMode(std::string inputFileName, std::string outputFileName, int iterations);
    void StartOnlineMode(std::string inputFileName);
    void Help();
public:
    ConsoleController();
    void Start(int argc, char** argv);
};


#endif //LAB_2_CONSOLECONTROLLER_H
