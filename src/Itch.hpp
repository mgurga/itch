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

#include "DebugWindow.hpp"
#include "FileHandler.hpp"
#include "ItchOptions.hpp"
#include "Project.hpp"
#include "engine/Engine.hpp"
#include "player/Player.hpp"

class Itch {
public:
    Itch(ItchOptions& io);
    ~Itch() {
        delete player;
        delete debug_window;
    }

    void init();
    void draw();

    void load_from_folder(std::filesystem::path sb3_folder);
    void load_from_file(std::filesystem::path sb3_file);
    void load_from_url(std::string project_url);

    Project project;
    EngineFunctions::Engine engine;
    Player* player = nullptr;
    DebugWindow* debug_window = nullptr;

    ItchOptions& options;

private:
    bool pause_engine = false;
};