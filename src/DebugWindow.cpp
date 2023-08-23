#include "DebugWindow.hpp"

void DebugWindow::draw() {
    if (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
                running = false;
            }
        }

        ImGui::SFML::Update(window, clock.getElapsedTime());
        draw_imgui();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
}

void DebugWindow::draw_imgui() {
    ImGui::SetNextWindowPos({5, 5}, ImGuiCond_FirstUseEver);
    ImGui::Begin("Engine Playback");
    if (ImGui::Button(pause_engine ? "Resume Engine" : "Pause Engine"))
        pause_engine = !pause_engine;
    ImGui::SameLine();
    if (ImGui::Button("Run 1 Tick")) {
        EMPTY_PLAYER_INFO(pi);
        eng->tick(&pi);
    }
    ImGui::SameLine();
    if (ImGui::Button("Run 10 Ticks")) {
        EMPTY_PLAYER_INFO(pi);
        for (int i = 0; i < 10; i++) eng->tick(&pi);
    }
    if (tps_clock.getElapsedTime().asSeconds() >= 1) {
        tps = eng->ticks - ticks_delta;
        tps_clock.restart();
        ticks_delta = eng->ticks;
    }
    ImGui::Text("ticks: %llu   ticks per second: %d", eng->ticks, tps);
    ImGui::End();
}