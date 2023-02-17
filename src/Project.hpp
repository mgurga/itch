#pragma once
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Project {
public:
    Project();
    Project(std::string pjf);

    std::string project_file_name;
    json project_json;

    void load_from_project_json();
};