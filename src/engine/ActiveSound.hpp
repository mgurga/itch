#pragma once

#include <chrono>

#include "../scratch/ScratchSound.hpp"

class ActiveSound {
public:
    ActiveSound(ScratchSound& snd) :
        sound(snd),
        start_time(std::chrono::high_resolution_clock::now()),
        end_time(std::chrono::high_resolution_clock::now() +
                 std::chrono::milliseconds(static_cast<long>(snd.sound.get_length() * 1000))) {}

    bool finished() const { return end_time <= std::chrono::high_resolution_clock::now(); }
    ScratchSound& get_sound() { return sound; }
    std::chrono::time_point<std::chrono::high_resolution_clock> get_end_time() { return end_time; }

private:
    ScratchSound& sound;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};