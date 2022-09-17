#include <iostream>

#include "lib/json.h"

class Commands{
    public:
        nlohmann::json commands;
        void loadCommandsJSON(std::string filename);
};