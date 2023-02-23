#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchBlock
{
public:
    ScratchBlock(json sb, std::string id);

    std::string id;

    std::string opcode;
    std::string next;
    std::string parent;
    json inputs;
    json fields;
    bool shadow, topLevel;
    int x, y;
};
