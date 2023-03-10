#include <iostream>
#include <string>
#include <filesystem>
#include <SFML/Window.hpp>

#include "Itch.hpp"

int main(int argc, char *argv[]) {
    std::cout << "itch - Scratch 3 project player" << std::endl;

    if (argc <= 1 || argc >= 3) {
        std::cout << "incorrect number of arguments." << std::endl << "proper syntax is:" << std::endl;
#if WIN32
        std::cout << "\titch.exe example.sb3" << std::endl;
#else
        std::cout << "\titch example.sb3" << std::endl;
#endif
        exit(1);
    }

    std::filesystem::path filepath = argv[1];
    if (!std::filesystem::exists(filepath)) {
        std::cout << "file '" << filepath << "' does not exists." << std::endl;
        return 1;
    }

    Itch itch = Itch(filepath);

    while(itch.running) {
        itch.draw();
    }

    return 0;
}