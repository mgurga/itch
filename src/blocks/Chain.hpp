#pragma once

#include <chrono>
#include <nlohmann/json.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "../scratch/ScratchBlock.hpp"
#include "Link.hpp"
#include "Opcodes.hpp"

using json = nlohmann::json;

struct ResumePoint {
    int link_num;  // link to resume at
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::optional<std::chrono::time_point<std::chrono::high_resolution_clock>> end_time;
    double runs = -1;
};

class Chain {
public:
    Chain(){};

    void add_link(const Link l) { links.push_back(l); }
    Link& get_header() { return links.at(0); }
    Link& get_link(int n) { return links.at(n); }
    unsigned int size() { return links.size(); }

    bool is_activatable() { return activatable; }
    void set_activatable(bool b) { activatable = b; }

    static std::vector<Chain> create_chains(std::vector<ScratchBlock> blocks);
    friend std::ostream& operator<<(std::ostream& os, const Chain& c);

    std::vector<ResumePoint> continue_at;

private:
    bool activatable = true;  // set to true if the first link is of type event
    std::vector<Link> links;
};