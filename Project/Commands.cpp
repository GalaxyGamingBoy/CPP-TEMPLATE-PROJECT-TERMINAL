#include <iostream>
#include <fstream>

#include "Commands.h"
#include "lib/json.h"

/**
 * @brief
 *
 * @param filename The name of the command JSON File
 */
void Commands::loadCommandsJSON(std::string filename)
{
    Commands::commands = nlohmann::json::parse(std::ifstream(filename));
}
