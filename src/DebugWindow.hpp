#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Project.hpp"
#include "engine/Engine.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

class DebugWindow {
public:
    DebugWindow(EngineFunctions::Engine* e, Project* p, bool& pe, bool& r) :
        running(r), pause_engine(pe) {
        eng = e;
        prj = p;
        window.create(sf::VideoMode(300, 500), "Itch Debug");
        ImGui::SFML::Init(window, true);
        ImGui::GetIO().IniFilename = NULL;
    }
    void draw();

private:
    void draw_imgui();

    EngineFunctions::Engine* eng;
    Project* prj;
    sf::RenderWindow window;
    sf::Clock clock;
    bool& running;
    bool& pause_engine;
};