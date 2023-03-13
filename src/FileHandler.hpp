#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class FileHandler {
public:
    FileHandler(std::filesystem::path file_path, std::filesystem::path temp_dir);
    bool initialized = false;
    std::filesystem::path file_name; // .sb3 filename
    std::string file_name_no_ext;
    std::filesystem::path temp_dir;

    json project_json;

    // unzip the sb3 file
    void init(std::function<void()> callback);
};