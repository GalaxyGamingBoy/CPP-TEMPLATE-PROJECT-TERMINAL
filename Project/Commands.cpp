#include <iostream>
#include <fstream>

#include "Commands.h"
#include "lib/json.h"

void Commands::loadCommandsJSON(std::string filename)
{
    Commands::commands = nlohmann::json::parse(std::ifstream(filename));
}
