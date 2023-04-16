#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#if BUILD_NETWORK_SUPPORT
#include <cpr/cpr.h>
#endif

#include "Project.hpp"
#include "player/Player.hpp"
#include "engine/Engine.hpp"
#include "FileHandler.hpp"

class Itch {
public:
    Itch();

    void load_from_file(std::filesystem::path sb3_file);
    void load_from_url(std::string project_url);

    void draw();

    Project project;
    EngineFunctions::Engine engine;
    Player player;

    bool running = true;
    const std::filesystem::path temp_dir{"temp"};
};