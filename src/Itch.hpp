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