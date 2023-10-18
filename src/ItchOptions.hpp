#pragma once

#include <filesystem>
#include <string>

struct ItchOptions {
    bool headless = false;
    bool debugwindow = false;
    bool running = true;
    std::string username = "";
    std::filesystem::path tempdir = "temp/";
};