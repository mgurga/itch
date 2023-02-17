#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <csignal>

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

    Itch itch = Itch(std::string(argv[1]));

    while(itch.running) {
        itch.draw();
    }

    return 0;
}