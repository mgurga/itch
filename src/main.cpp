#include <CLI/CLI.hpp>
#include <filesystem>
#include <iostream>
#include <string>

#include "Itch.hpp"

int main(int argc, char *argv[]) {
    CLI::App app{"itch - Scratch 3 project player"};

    std::string resource = "";
    bool headless = false;
    app.add_flag("-l,--headless", headless, "run itch without graphics");
    app.add_option(".sb3/url/folder", resource, ".sb3 file path or scratch.mit.edu URL")
        ->default_val("temp/");
    CLI11_PARSE(app, argc, argv);

    Itch itch;
    itch.headless = headless;
    itch.init();
    if (resource.find("scratch.mit.edu") == std::string::npos) {
        std::filesystem::path filepath = resource;
        if (!std::filesystem::exists(filepath)) {
            std::cout << "file/folder '" << filepath << "' does not exists." << std::endl;
            return 1;
        }
        if (filepath.extension() == ".sb3") {
            itch.load_from_file(filepath);
        } else {
            itch.load_from_folder(filepath);
        }
    } else {
        itch.load_from_url(resource);
    }

    while (itch.running) { itch.draw(); }

    return 0;
}