#pragma once
#include <string>
#include <iostream>
#include <filesystem>

#include "Project.hpp"

class Itch {
public:
    Project project;
    bool running = true;

    std::string temp_dir = "temp/";

    Itch(std::string sb3_file);
    void draw();
};