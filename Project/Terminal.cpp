#include <iostream>

#include "Terminal.h"

/**
 * @brief Starts the virtual terminal
 *
 */
void Terminal::startTerminal()
{
    Terminal::isTerminalRunning = true;
    Terminal::commandList.loadCommandsJSON("res/commands.json");
    Terminal::mainLoop();
}

/**
 * @brief The virtual terminal main loop
 *
 */
void Terminal::mainLoop()
{
    while (Terminal::isTerminalRunning)
    {
        Terminal::runCMD(Terminal::askCMD());
    }
}

/**
 * @brief Asks user for the command to run
 *
 * @return std::string
 */
std::string Terminal::askCMD()
{
    std::string cmd;
    std::cout << Terminal::hostname + " ~ " + Terminal::startCMDPrefix;
    std::cin >> cmd;
    return cmd;
}

/**
 * @brief Finds the id of the command and runs it
 *
 * @param cmd The command to find the id & run
 * @return int The command return code
 */
int Terminal::runCMD(std::string cmd)
{
    for (nlohmann::json obj : Terminal::commandList.commands)
    {
        for (std::string name : obj["names"])
        {
            if (name == cmd)
                return Terminal::cmdFinder(obj["id"]);
        }
    }
    return 404;
}

/**
 * @brief Runs a command
 *
 * @param id The command ID to run
 * @return int The command return code
 */
int Terminal::cmdFinder(int id)
{
    // Every command ID can be found on the command JSON File
    switch (id)
    {
    case 0: // Exit
        Terminal::isTerminalRunning = false;
        std::cout << "Console Exited" << std::endl;
        return 0;
    case 1: // Version
        std::cout << "Terminal Version: v" << Terminal::version << std::endl;
        return 0;
    case 2: // Help
        std::cout << "Help Menu - Command List\n\n"
                  << "  id   | name  |  help\n"
                  << "-------|-------|-------" << std::endl;
        for (nlohmann::json obj : Terminal::commandList.commands)
        {
            std::cout << obj["id"] << " | " << (std::string)obj["names"][0] << " | " << (std::string)obj["help"] << std::endl;
        }
        return 0;
    case 3: // View Command Aliases
    {
        std::string commandToCheck = "";
        int commandID = 0;
        commandToCheck = Terminal::getUserInput("Menu - View Command Aliases", "commandToCheck: ");
        std::cout << "Aliases: ";

        // Find command ID
        for (nlohmann::json obj : Terminal::commandList.commands)
        {
            for (std::string name : obj["names"])
            {
                if (name == commandToCheck)
                    commandID = obj["id"];
            }
        }

        // Display aliases
        for (nlohmann::json obj : Terminal::commandList.commands)
        {
            if (obj["id"] == commandID)
            {
                for (std::string name : obj["names"])
                {
                    std::cout << name << " ";
                }
            }
        }
        std::cout << std::endl;
        return 0;
    }
    case 4: // Change Hostname
        Terminal::hostname = Terminal::getUserInput("Settings - Change Hostname", "newHostname: ");
        return 0;
    case 5: // Change prefix
        Terminal::startCMDPrefix = Terminal::getUserInput("Settings - Change Prefix", "newPrefix: ") + " ";
        return 0;
    }
    return 404;
}

/**
 * @brief Gets user input
 *
 * @param label The label to show ( i.e. Section - Menu )
 * @param query What to ask the user ( i.e. label: )
 * @return std::string The user response
 */
std::string Terminal::getUserInput(std::string label, std::string query)
{
    std::string queryResult = "";
    std::cout << label << std::endl;
    std::cout << query;
    std::cin >> query;
    return query;
}