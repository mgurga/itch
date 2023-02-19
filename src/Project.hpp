#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "scratch/ScratchTarget.hpp"
#include "scratch/ScratchMeta.hpp"

using json = nlohmann::json;

class Project {
public:
    Project();
    Project(std::string pjf);

    std::string project_file_name;
    json project_json;

    void load_from_project_json();

    std::vector<ScratchTarget> targets;
    std::vector<std::string> extensions;
    ScratchMeta meta;
};