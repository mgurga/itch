#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "../scratch/ScratchBlock.hpp"
#include "Link.hpp"

using json = nlohmann::json;

class Chain {
public:
    Chain(std::vector<ScratchBlock> blocks);

    bool activatable; // set to true if the first link is of type event

    std::vector<Link> links;
};