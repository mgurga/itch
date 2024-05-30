#pragma once

#include <filesystem>
#include <string>

struct ItchOptions {
    bool headless = false;
    bool debugwindow = false;
    bool running = true;
    std::string username = "";
    std::filesystem::path tempdir = "temp/";
    int width = 480;
    int height = 360;
    float scale = 1;
};