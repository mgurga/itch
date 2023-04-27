#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../blocks/Chain.hpp"
#include "../blocks/Link.hpp"
#include "ScratchBlock.hpp"
#include "ScratchCostume.hpp"
#include "ScratchList.hpp"
#include "ScratchSound.hpp"
#include "ScratchVariable.hpp"

using json = nlohmann::json;

class ScratchTarget {
public:
    ScratchTarget();
    ScratchTarget(json st, std::filesystem::path temp_dir, bool heavyload = true);

    bool isStage;
    std::string name;
    std::vector<ScratchVariable> variables;
    std::vector<ScratchList> lists;
    std::vector<ScratchCostume> costumes;
    std::vector<ScratchSound> sounds;
    std::vector<ScratchBlock> blocks;
    std::vector<Link> links;
    unsigned int volume;
    int layerOrder;
    unsigned int currentCostume;

    std::vector<Chain> chains;
};
