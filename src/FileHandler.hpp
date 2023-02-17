#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "Itch.hpp"

using json = nlohmann::json;

class FileHandler {
public:
    FileHandler(std::string file_name, Itch& itch);
    bool initialized = false;
    std::string file_name; // .sb3 filename
    std::string file_name_no_ext;

    json project_json;

    // unzip the sb3 file
    void init(std::function<void()> callback);

private:
    Itch& itch;
};