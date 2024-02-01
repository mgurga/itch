#include "Engine.hpp"

void EngineFunctions::Engine::play_sound(Link link, ScratchTarget* s) {
    std::string soundfile = compute_input(link.inputs["SOUND_MENU"], s);
    for (ScratchSound& ss : s->sounds)
        if (ss.name == soundfile) active_sounds.push_back(ActiveSound(ss));
}

void EngineFunctions::Engine::play_sound_until_done(Link link, Chain& c, ScratchTarget* s, int& i) {
    if (!c.continue_at.empty() && c.continue_at.back().end_time.has_value()) {
        if (c.continue_at.back().end_time <= std::chrono::high_resolution_clock::now()) {
            c.continue_at.pop_back();
        } else {
            i = -1;
        }
    } else {
        std::string soundfile = compute_input(link.inputs["SOUND_MENU"], s);
        for (ScratchSound& ss : s->sounds)
            if (ss.name == soundfile) active_sounds.push_back(ActiveSound(ss));

        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = active_sounds.back().get_end_time();
        c.continue_at.push_back(rp);
        i = -1;
    }
}
