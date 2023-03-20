#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(Link link, ScratchSprite* s) {
    double dir = (s->direction - 90) * (3.1415926 / 180);
    double steps = std::get<double>(compute_input(link.inputs["STEPS"]));
    s->x = s->x + (steps * cos(dir));
    s->y = s->y + (steps * sin(dir));
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
        std::cout << "new sprite position: " << s->x << ", " << s->y << std::endl;
    } else if (target == "_mouse_") {
        s->x = pi->mouse_pos.x - 240;
        s->y = -pi->mouse_pos.y + 180;
    } else {
        std::cout << "unknown go_to_menu entry: " << target << std::endl;
    }
}