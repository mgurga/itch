#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

using json = nlohmann::json;

#if BUILD_NETWORK_SUPPORT
#include <cpr/cpr.h>
#endif

#include "FileHandler.hpp"
#include "Project.hpp"
#include "engine/Engine.hpp"
#include "player/Player.hpp"

class Itch {
public:
    Itch(){};
    ~Itch() { delete player; }

    void init();
    void draw();

    void load_from_folder(std::filesystem::path sb3_folder);
    void load_from_file(std::filesystem::path sb3_file);
    void load_from_url(std::string project_url);

    Project project;
    EngineFunctions::Engine engine;
    Player* player = nullptr;

    bool running = true;
    bool headless = false;  // run without rendering code (engine only)
    const std::filesystem::path temp_dir{"temp"};
};