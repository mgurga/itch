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
            if (s->costumes.at(i).name == new_costume.get_string()) s->currentCostume() = i;
    } else {
        s->currentCostume() = new_costume.get_number() - 1;
    }
}

void EngineFunctions::Engine::next_costume(ScratchTarget *s) {
    s->currentCostume()++;
    if (s->currentCostume() == s->costumes.size()) s->currentCostume() = 0;
}

void EngineFunctions::Engine::go_to_layer(std::string frontorback, ScratchTarget *s) {
    if (frontorback == "front") {
        s->layerOrder() = 999 + fronts;
        fronts++;
    } else {
        s->layerOrder() = -999 - backs;
        backs++;
    }
}

void EngineFunctions::Engine::change_layer_by(Link link, ScratchTarget *s) {
    if (link.fields["FORWARD_BACKWARD"][0] == "forward") {
        s->layerOrder() += compute_input(link.inputs["NUM"], s).get_number();
    } else {
        s->layerOrder() -= compute_input(link.inputs["NUM"], s).get_number();
    }
}

void EngineFunctions::Engine::set_effect_to(Link link, ScratchTarget *s) {
    std::string effect = link.fields["EFFECT"][0];
    std::transform(effect.begin(), effect.end(), effect.begin(), ::toupper);

    try {
        s->effects()[effect] = compute_input(link.inputs["VALUE"], s);
    } catch (const std::exception &e) {
        std::cout << "failed to set effect: '" << effect << "' ";
        std::cout << "with error: " << e.what() << std::endl;
    }
}

void EngineFunctions::Engine::change_effect_by(Link link, ScratchTarget *s) {
    std::string effect = link.fields["EFFECT"][0];
    std::transform(effect.begin(), effect.end(), effect.begin(), ::toupper);

    try {
        s->effects()[effect] += compute_input(link.inputs["VALUE"], s).get_number();
    } catch (const std::exception &e) {
        std::cout << "failed to change effect: '" << effect << "' ";
        std::cout << "with error: " << e.what() << std::endl;
    }
}