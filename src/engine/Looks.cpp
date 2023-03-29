#include "Engine.hpp"
#include "SpriteMessage.hpp"

void EngineFunctions::Engine::say(Link link, ScratchSprite *s) {
    std::string msg = variant_str(compute_input(link.inputs["MESSAGE"]));
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
        std::string msg = variant_str(compute_input(link.inputs["MESSAGE"]));
        double dur = std::get<double>(compute_input(link.inputs["SECS"]));
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