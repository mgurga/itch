#include "Engine.hpp"

void EngineFunctions::Engine::say(Link link, ScratchTarget *s) {
    std::string msg = compute_input(link.inputs["MESSAGE"], s).get_string();
    say_logs.push_back(SpriteMessage(msg, s, 0));
    std::cout << say_logs.back() << std::endl;
}

void EngineFunctions::Engine::say_for_sec(Link link, ScratchTarget *s, Chain &c, int &i) {
    if (!c.continue_at.empty() && c.continue_at.back().end_time.has_value()) {
        if (c.continue_at.back().end_time <= std::chrono::high_resolution_clock::now()) {
            c.continue_at.pop_back();
        } else {
            i = -1;
        }
    } else {
        std::string msg = compute_input(link.inputs["MESSAGE"], s).get_string();
        double dur = compute_input(link.inputs["SECS"], s).get_number();
        say_logs.push_back(SpriteMessage(msg, s, dur));
        std::cout << say_logs.back() << std::endl;

        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = say_logs.back().end_time;
        c.continue_at.push_back(rp);
        i = -1;
    }
}

void EngineFunctions::Engine::switch_costume_to(Link link, ScratchTarget *s) {
    Value new_costume = compute_input(link.inputs["COSTUME"], s);

    if (new_costume.contains_string()) {
        for (int i = 0; i < s->costumes.size(); i++)
            if (s->costumes.at(i).name == new_costume.get_string()) s->set_current_costume(i);
    } else {
        s->set_current_costume(new_costume.get_number() - 1);
    }
}

void EngineFunctions::Engine::next_costume(ScratchTarget *s) {
    s->set_current_costume(s->get_current_costume() + 1);
    if (s->get_current_costume() == s->costumes.size()) s->set_current_costume(0);
}

void EngineFunctions::Engine::go_to_layer(std::string frontorback, ScratchTarget *s) {
    if (frontorback == "front") {
        s->set_layer_order(999 + fronts);
        fronts++;
    } else {
        s->set_layer_order(-999 - backs);
        backs++;
    }
}

void EngineFunctions::Engine::change_layer_by(Link link, ScratchTarget *s) {
    if (link.fields["FORWARD_BACKWARD"][0] == "forward") {
        s->set_layer_order(s->get_layer_order() +
                           compute_input(link.inputs["NUM"], s).get_number());
    } else {
        s->set_layer_order(s->get_layer_order() -
                           compute_input(link.inputs["NUM"], s).get_number());
    }
}