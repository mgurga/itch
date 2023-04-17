#include "Engine.hpp"

void EngineFunctions::Engine::say(Link link, ScratchSprite *s) {
    std::string msg = compute_input(link.inputs["MESSAGE"]).get_string();
    say_logs.push_back(SpriteMessage(msg, s, 0));
}

void EngineFunctions::Engine::say_for_sec(Link link, ScratchSprite *s, Chain& c, int& i) {
    if (!c.continue_at.empty() && c.continue_at.back().end_time.has_value()) {
        if (c.continue_at.back().end_time <= std::chrono::high_resolution_clock::now()) {
            c.continue_at.pop_back();
        } else {
            i = -1;
        }
    } else {
        std::string msg = compute_input(link.inputs["MESSAGE"]).get_string();
        double dur = compute_input(link.inputs["SECS"]).get_number();
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

void EngineFunctions::Engine::switch_costume_to(Link link, ScratchSprite *s) {
    ScratchBlock costume_shadow = get_sb_by_id(link.inputs["COSTUME"][1]);
    std::string new_costume_name = costume_shadow.fields["COSTUME"][0];

    for (int i = 0; i < s->costumes.size(); i++)
        if (s->costumes.at(i).name == new_costume_name)
            s->currentCostume = i;
}

void EngineFunctions::Engine::next_costume(ScratchSprite *s) {
    s->currentCostume++;
    if (s->currentCostume == s->costumes.size())
        s->currentCostume = 0;
}