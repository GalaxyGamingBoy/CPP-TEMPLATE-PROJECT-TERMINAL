#include <iostream>

#include "lib/json.h"

/**
 * @brief The Commands class
 *
 */
class Commands
{
public:
    nlohmann::json commands;
    void loadCommandsJSON(std::string filename);
};