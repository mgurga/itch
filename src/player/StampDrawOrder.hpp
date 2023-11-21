#pragma once

#include <string>

#include "../scratch/ScratchSprite.hpp"
#include "DrawOrder.hpp"

class StampDrawOrder : public DrawOrder {
public:
    StampDrawOrder(double x, double y, ScratchSprite& ss) :
        DrawOrder(x, y, DrawObject::PEN_STAMP), sprite(ss) {}

    ScratchSprite& get_sprite() const { return sprite; }

private:
    double x, y;
    ScratchSprite& sprite;
};