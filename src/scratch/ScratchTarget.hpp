#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "ScratchVariable.hpp"
#include "ScratchCostume.hpp"
#include "ScratchSound.hpp"
#include "ScratchBlock.hpp"
#include "../blocks/Chain.hpp"

using json = nlohmann::json;

class ScratchTarget
{
public:
    ScratchTarget();
    ScratchTarget(json st, std::filesystem::path temp_dir, bool heavyload = true);

    bool isStage;
    std::string name;
    std::vector<ScratchVariable> variables;
    std::vector<ScratchCostume> costumes;
    std::vector<ScratchSound> sounds;
    std::vector<ScratchBlock> blocks;
    int volume;
    int layerOrder;
    int currentCostume;

    std::vector<Chain> chains;
};
