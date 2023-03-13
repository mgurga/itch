#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

#include "scratch/ScratchStage.hpp"
#include "scratch/ScratchSprite.hpp"
#include "scratch/ScratchMeta.hpp"
#include "scratch/ScratchMonitor.hpp"

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
    std::vector<ScratchMonitor> monitors;
    std::vector<std::string> extensions;
    ScratchMeta meta;
};