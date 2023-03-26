#include "Engine.hpp"
#include <chrono>

void EngineFunctions::Engine::wait(double duration, Chain& c, int& i) {
    if (c.continue_at.has_value()) {
        if (c.continue_at->end_time <= std::chrono::high_resolution_clock::now()) {
            c.continue_at = {};
        } else {
            i = -1;
        }
    } else {
        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = std::chrono::high_resolution_clock::now();
        rp.end_time += std::chrono::seconds(static_cast<long>(duration));
        c.continue_at = rp;
        i = -1;
    }
}

void EngineFunctions::Engine::forever_loop(Link link, Chain& c, int& i) {
    
}