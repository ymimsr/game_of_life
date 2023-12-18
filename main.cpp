#include "controller/ConsoleController.h"

int main(int argc, char** argv) {
    auto* consoleController = new class ConsoleController();
    consoleController->Start(argc, argv);

    return 0;
}
