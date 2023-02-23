#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Link {
public:
    Link(std::string opcode, std::string next, std::string parent);

    std::string opcode;
    std::string next;
    std::string parent;
};