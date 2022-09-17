#include <iostream>

#include "Terminal.h"

void Terminal::startTerminal()
{
    Terminal::isTerminalRunning = true;
    Terminal::commandList.loadCommandsJSON("res/commands.json");
    Terminal::mainLoop();
}

void Terminal::mainLoop()
{
    while (Terminal::isTerminalRunning)
    {
        Terminal::runCMD(Terminal::askCMD());
    }
}

std::string Terminal::askCMD()
{
    std::string cmd;
    std::cout << Terminal::hostname + " ~ " + Terminal::startCMDPrefix;
    std::cin >> cmd;
    return cmd;
}

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

int Terminal::cmdFinder(int id)
{
    switch (id)
    {
    case 0:
        Terminal::isTerminalRunning = false;
        std::cout << "Console Exited" << std::endl;
        return 0;
    case 1:
        std::cout << "Terminal Version: v" << Terminal::version << std::endl;
        return 0;
    case 2:
        std::cout << "Help Menu - Command List\n\n"
                  << "  id   | name  |  help\n"
                  << "-------|-------|-------" << std::endl;
        for (nlohmann::json obj : Terminal::commandList.commands)
        {
            std::cout << obj["id"] << " | " << (std::string)obj["names"][0] << " | " << (std::string)obj["help"] << std::endl;
        }
        return 0;
    case 3:
    {
        std::string commandToCheck = "";
        int commandID = 0;
        std::cout << "Menu - View Command Aliases" << std::endl;
        std::cout << "commandToCheck: ";
        std::cin >> commandToCheck;
        std::cout << "Aliases: ";

        for (nlohmann::json obj : Terminal::commandList.commands)
        {
            for (std::string name : obj["names"])
            {
                if (name == commandToCheck)
                    commandID = obj["id"];
            }
        }

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
    case 4:
        Terminal::hostname = Terminal::getUserInput("Settings - Change Hostname", "newHostname: ");
        return 0;
    case 5:
        Terminal::startCMDPrefix = Terminal::getUserInput("Settings - Change Prefix", "newPrefix: ") + " ";
        return 0;
    }
    return 404;
}

std::string Terminal::getUserInput(std::string label, std::string query)
{
    std::string queryResult = "";
    std::cout << label << std::endl;
    std::cout << query;
    std::cin >> query;
    return query;
}