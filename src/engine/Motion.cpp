#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(double steps, ScratchTarget* s) {
    double dir = (s->get_direction() + 90) * (PI / 180);
    s->set_x(s->get_x() - (std::round((steps * cos(dir)) * 1000.0) / 1000.0));
    s->set_y(s->get_y() + (std::round((steps * sin(dir)) * 1000.0) / 1000.0));
}

void EngineFunctions::Engine::go_to_menu(Link link, ScratchTarget* s) {
    std::string target;
    try {
        Link& sb = get_link_by_id(link.inputs["TO"].sab.sab.str_value);
        target = sb.fields["TO"].at(0);
    } catch (const std::exception& e) { target = link.inputs["TO"].sab.sab.str_value; }

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

void EngineFunctions::Engine::set_rotation_style(std::string rs, ScratchTarget* s) {
    if (rs == "don't rotate") {
        s->set_rotation_style(RotationStyle::DONT_ROTATE);
    } else if (rs == "left-right") {
        s->set_rotation_style(RotationStyle::LEFT_RIGHT);
    } else {
        s->set_rotation_style(RotationStyle::ALL_AROUND);
    }
}

void EngineFunctions::Engine::glide_for_secs(Link link, ScratchTarget* s, Chain& c, int& i) {
    if (!c.continue_at.empty() && c.continue_at.back().end_time.has_value()) {
        GlideProgress* gp = nullptr;
        for (GlideProgress& g : glide_progresses)
            if (g.sprite == s) gp = &g;
        if (c.continue_at.back().end_time <= std::chrono::high_resolution_clock::now()) {
            if (gp != nullptr) s->set_x(gp->end_x);
            if (gp != nullptr) s->set_y(gp->end_y);
            glide_progresses.erase(std::remove_if(glide_progresses.begin(), glide_progresses.end(),
                                                  [&](GlideProgress gp) { return gp.sprite == s; }),
                                   glide_progresses.end());
            c.continue_at.pop_back();
        } else {
            if (gp != nullptr) gp->update();
            i = -1;
        }
    } else {
        double secs = compute_input(link.inputs["SECS"], s).get_number();
        double x_pos = compute_input(link.inputs["X"], s).get_number();
        double y_pos = compute_input(link.inputs["Y"], s).get_number();

        glide_progresses.push_back(GlideProgress(s, secs, x_pos, y_pos));

        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = std::chrono::high_resolution_clock::now();
        rp.end_time.value() += std::chrono::milliseconds(static_cast<long>(secs * 1000));
        c.continue_at.push_back(rp);
        i = -1;
    }
}