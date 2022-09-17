#include <iostream>

#include "Commands.h"

/**
 * @brief The virtual Terminal class
 *
 */
class Terminal
{
private:
    bool isTerminalRunning = false;
    std::string hostname = "template_terminal";
    std::string startCMDPrefix = "-=> ";
    std::string version = "1.0.0";

public:
    Commands commandList;
    void startTerminal();
    void mainLoop();
    std::string askCMD();
    std::string getUserInput(std::string label, std::string query);
    int runCMD(std::string cmd);
    int cmdFinder(int id);
};