#pragma once

#include <chrono>
#include <string>

#include "../scratch/ScratchSprite.hpp"

class SpriteMessage {
public:
    SpriteMessage(std::string msg, ScratchTarget* msgr, double dur = 0) :
        message(msg),
        messager(msgr),
        duration(dur),
        end_time(std::chrono::high_resolution_clock::now() +
                 std::chrono::seconds(static_cast<long>(dur))) {}

    friend std::ostream& operator<<(std::ostream& os, const SpriteMessage& sm) {
        os << sm.messager->get_name() << " says \"" << sm.message << "\"";
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
    ScratchTarget* messager;
    double duration;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};