#pragma once

#include <chrono>

#include "../scratch/ScratchSprite.hpp"

class GlideProgress {
public:
    GlideProgress(ScratchTarget* sprite, double dur, double end_x, double end_y) :
        sprite(sprite),
        start_time(std::chrono::high_resolution_clock::now()),
        end_time(std::chrono::high_resolution_clock::now() +
                 std::chrono::milliseconds(static_cast<long>(dur * 1000))),
        end_x(end_x),
        end_y(end_y),
        start_x(sprite->get_x()),
        start_y(sprite->get_y()) {}

    void update() {
        double progress =
            static_cast<double>((start_time - std::chrono::high_resolution_clock::now()).count()) /
            static_cast<double>((start_time - end_time).count());

        sprite->set_x(start_x + ((end_x - start_x) * progress));
        sprite->set_y(start_y + ((end_y - start_y) * progress));
    }

    const bool finished() const { return end_time <= std::chrono::high_resolution_clock::now(); }

    ScratchTarget* sprite;
    double end_x, end_y;
    double start_x, start_y;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};