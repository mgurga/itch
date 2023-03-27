#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <vector>
#include <chrono>
#include <optional>

#include "../scratch/ScratchBlock.hpp"
#include "Link.hpp"
#include "Opcodes.hpp"

using json = nlohmann::json;

struct ResumePoint {
    int link_num; // link to resume at
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::optional<std::chrono::time_point<std::chrono::high_resolution_clock>> end_time;
};

class Chain {
public:
    Chain() {};

    bool activatable = true; // set to true if the first link is of type event
    std::vector<Link> links;
    std::vector<ResumePoint> continue_at;

    friend std::ostream & operator<<(std::ostream &os, const Chain& c);

    static std::vector<Chain> create_chains(std::vector<ScratchBlock> blocks);
};