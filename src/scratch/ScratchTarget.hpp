#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "ScratchVariable.hpp"
#include "ScratchCostume.hpp"
#include "ScratchSound.hpp"

using json = nlohmann::json;

class ScratchTarget
{
public:
    ScratchTarget();
    ScratchTarget(json st, std::string temp_dir, bool heavyload = true);

    bool isStage;
    std::string name;
    std::vector<ScratchVariable> variables;
    std::vector<ScratchCostume> costumes;
    std::vector<ScratchSound> sounds;
    int volume;
    int layerOrder;
    int currentCostume;
};
