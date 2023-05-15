#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "scratch/ScratchMeta.hpp"
#include "scratch/ScratchMonitor.hpp"
#include "scratch/ScratchSprite.hpp"
#include "scratch/ScratchStage.hpp"

using json = nlohmann::json;

class Project {
public:
    Project();
    Project(std::filesystem::path pjf);

    std::filesystem::path temp_dir;
    json project_json;

    void load_from_project_json(bool heavyload = true);

    ScratchStage stage;
    std::vector<ScratchSprite> sprites;
    std::vector<ScratchSprite> clones;  // NOT A PART OF project.json.
    std::vector<ScratchMonitor> monitors;
    std::vector<std::string> extensions;
    ScratchMeta meta;
};