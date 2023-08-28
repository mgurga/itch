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
    ImGui::SetNextWindowSize({290, 71}, ImGuiCond_FirstUseEver);
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

    ImGui::SetNextWindowPos({5, height_offset}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize({290, 120}, ImGuiCond_FirstUseEver);
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
    height_offset += ImGui::GetWindowHeight() + 5;
    ImGui::End();

    ImGui::SetNextWindowPos({5, height_offset}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize({290, 120}, ImGuiCond_FirstUseEver);
    ImGui::Begin("Sprites");
    for (ScratchSprite& spr : prj->sprites) {
        if (ImGui::CollapsingHeader(spr.get_name().c_str())) {
            ImGui::PushItemWidth(50.0f);
            ImGui::Text("x");
            ImGui::SameLine();
            float xpos = spr.get_x();
            if (ImGui::DragFloat(" ", &xpos)) spr.set_x(xpos);
            ImGui::SameLine();
            ImGui::Text("y");
            ImGui::SameLine();
            float ypos = spr.get_y();
            if (ImGui::DragFloat("##ypos ", &ypos)) spr.set_y(ypos);
            ImGui::SameLine();
            ImGui::Text(" visible");
            ImGui::SameLine();
            bool visible = spr.get_visible();
            if (ImGui::Checkbox("##visible", &visible)) spr.set_visible(visible);
            ImGui::Text("dir");
            ImGui::SameLine();
            float dir = spr.get_direction();
            if (ImGui::DragFloat("##dir", &dir)) spr.set_direction(dir);
            ImGui::SameLine();
            ImGui::Text(" size");
            ImGui::SameLine();
            int size = spr.get_size();
            ImGui::PushItemWidth(40.0f);
            if (ImGui::DragInt("##size", &size)) spr.set_size(size);
            ImGui::SameLine();
            ImGui::Text(" layer");
            ImGui::SameLine();
            int layer = spr.get_layer_order();
            ImGui::PushItemWidth(30.0f);
            if (ImGui::DragInt("##layer", &layer)) spr.set_layer_order(layer);
            ImGui::Text("costume");
            ImGui::SameLine();
            std::string selected = spr.costume().name;
            ImGui::PushItemWidth(150.0f);
            if (ImGui::BeginCombo(
                    (std::to_string(spr.get_current_costume() + 1) + " ##costumedropdown").c_str(),
                    selected.c_str())) {
                for (ScratchCostume& c : spr.costumes) {
                    bool is_selected = (c.name == selected);
                    if (ImGui::Selectable(c.name.c_str(), is_selected)) {
                        selected = c.name;
                        for (int i = 0; i < spr.costumes.size(); i++)
                            if (spr.costumes.at(i).name == c.name) spr.set_current_costume(i);
                    }
                    if (is_selected) ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
    }
    ImGui::End();
}