#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "ScratchArrayBlock.hpp"

using json = nlohmann::json;

class ScratchBlock
{
public:
    ScratchBlock() {};
    ScratchBlock(json sb, std::string id);

    std::string id;

    std::string opcode;
    std::string next;
    std::string parent;
    json inputs;
    json fields;
    bool shadow, topLevel;
    int x, y;

    bool is_array_block;
    ScratchArrayBlock array_block;
};
