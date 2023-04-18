#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(double steps, ScratchSprite* s) {
    double dir = (s->direction + 90) * (3.141592653589793 / 180);
    s->x -= std::round((steps * cos(dir)) * 1000.0) / 1000.0;
    s->y += std::round((steps * sin(dir)) * 1000.0) / 1000.0;
}

void EngineFunctions::Engine::go_to_menu(Link link, ScratchSprite* s) {
    ScratchBlock sb = get_sb_by_id(link.inputs["TO"][1].get<std::string>());
    std::string target = sb.fields["TO"][0].get<std::string>();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> randwidth(-240, 240);
    std::uniform_int_distribution<int> randheight(-180, 180);

    if (target == "_random_") {
        s->x = static_cast<double>(randwidth(rng));
        s->y = static_cast<double>(randheight(rng));
    } else if (target == "_mouse_") {
        s->x = pi->mouse_pos.x;
        s->y = pi->mouse_pos.y;
    } else {
        std::cout << "unknown go_to_menu entry: " << target << std::endl;
    }
}