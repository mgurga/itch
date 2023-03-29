#pragma once

#include <string>
#include <chrono>

#include "../scratch/ScratchSprite.hpp"

class SpriteMessage {
public:
    SpriteMessage(std::string msg, ScratchSprite* msgr, double dur = 0):
        message(msg),
        messager(msgr),
        duration(dur),
        end_time(std::chrono::high_resolution_clock::now() + std::chrono::seconds(static_cast<long>(dur)))
    {}

    friend std::ostream& operator<<(std::ostream &os, const SpriteMessage& sm) {
        os << sm.messager->name << " says \"" << sm.message << "\"";
        if (sm.duration != 0) {
            os << " for " << sm.duration;
            if (sm.duration > 1.0) {
                os << " seconds";
            } else {
                os << " second";
            }
        }
        return os;
    }

    std::string message;
    ScratchSprite* messager;
    double duration;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};