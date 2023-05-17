#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(double steps, ScratchTarget* s) {
    double dir = (s->get_direction() + 90) * (3.141592653589793 / 180);
    s->set_x(s->get_x() - (std::round((steps * cos(dir)) * 1000.0) / 1000.0));
    s->set_y(s->get_y() + (std::round((steps * sin(dir)) * 1000.0) / 1000.0));
}

void EngineFunctions::Engine::go_to_menu(Link link, ScratchTarget* s) {
    Link& sb = get_link_by_id(link.inputs["TO"].sab.sab.str_value);
    std::string target = sb.fields["TO"].at(0);

    if (target == "_random_") {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> randwidth(-240, 240);
        std::uniform_int_distribution<int> randheight(-180, 180);

        s->set_x(static_cast<double>(randwidth(rng)));
        s->set_y(static_cast<double>(randheight(rng)));
    } else if (target == "_mouse_") {
        s->set_x(static_cast<double>(pi->mouse_x));
        s->set_y(static_cast<double>(pi->mouse_y));
    } else {
        try {
            ScratchTarget& t = get_target_by_name(target);

            s->set_x(t.get_x());
            s->set_y(t.get_y());
        } catch (const std::exception& e) {
            std::cout << "unknown go_to_menu entry: " << target << std::endl;
        }
    }
}