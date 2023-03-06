#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include <vector>
#include "../scratch/ScratchBlock.hpp"
#include "Link.hpp"
#include "Opcodes.hpp"

using json = nlohmann::json;

class Chain {
public:
    Chain() {};

    bool activatable = true; // set to true if the first link is of type event
    std::vector<Link> links;

    friend std::ostream & operator<<(std::ostream &os, const Chain& c);

    static std::vector<Chain> create_chains(std::vector<ScratchBlock> blocks);
};