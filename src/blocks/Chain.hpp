#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include <vector>
#include "../scratch/ScratchBlock.hpp"
#include "Link.hpp"

using json = nlohmann::json;

class Chain {
public:
    Chain();

    bool activatable = true; // set to true if the first link is of type event
    std::vector<Link> links;

    static std::vector<Chain> create_chains(std::vector<ScratchBlock> blocks);
};