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
    float height_offset = 5;

    ImGui::SetNextWindowPos({5, height_offset}, ImGuiCond_FirstUseEver);
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
    height_offset += ImGui::GetWindowHeight() + 5;
    ImGui::End();

    ImGui::SetNextWindowPos({5, height_offset});
    ImGui::SetNextWindowSize({290, 120});
    ImGui::Begin("Variables");
    for (Variable& var : eng->variables) {
        ImGui::PushItemWidth(40.0f);
        ImGui::Text("%s", var.name.c_str());
        ImGui::SameLine();
        std::string display_val = var.val().get_string();
        display_val.resize(100);
        std::string type = var.val().contains_string()   ? "string"
                           : var.val().contains_number() ? "double"
                                                         : "bool";
        type += ", " + var.get_id().value_or("none");
        if (ImGui::InputText(type.c_str(), display_val.data(), IM_ARRAYSIZE(display_val.c_str()),
                             ImGuiInputTextFlags_EnterReturnsTrue)) {
            display_val.erase(std::find(display_val.begin(), display_val.end(), '\0'),
                              display_val.end());
            var = Value(display_val);
        }
    }
    ImGui::End();
}