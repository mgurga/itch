#pragma once
#include <string>
#include <iostream>
#include <filesystem>

#include "Project.hpp"
#include "player/Player.hpp"
#include "engine/Engine.hpp"

class Itch {
public:
    Itch(std::string sb3_file);
    void draw();

    Project project;
    EngineFunctions::Engine engine;
    Player player;

    bool running = true;
    std::string temp_dir = "temp/";
};