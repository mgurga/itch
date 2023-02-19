#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "scratch/ScratchTarget.hpp"
#include "scratch/ScratchMeta.hpp"
#include "scratch/ScratchMonitor.hpp"

using json = nlohmann::json;

class Project {
public:
    Project();
    Project(std::string pjf);

    std::string temp_dir;
    json project_json;

    void load_from_project_json();

    std::vector<ScratchTarget> targets;
    std::vector<ScratchMonitor> monitors;
    std::vector<std::string> extensions;
    ScratchMeta meta;
};