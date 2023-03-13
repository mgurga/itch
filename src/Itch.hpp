#pragma once

#include <string>
#include <iostream>
#include <filesystem>

#include "Project.hpp"
#include "player/Player.hpp"
#include "engine/Engine.hpp"
#include "FileHandler.hpp"

class Itch {
public:
    Itch(std::filesystem::path sb3_file);
    void draw();

    Project project;
    EngineFunctions::Engine engine;
    Player player;

    bool running = true;
    const std::filesystem::path temp_dir{"temp"};
};