#pragma once

#include "../scratch/ScratchSprite.hpp"
#include "DrawOrder.hpp"

class SpriteDrawOrder : public DrawOrder {
public:
    SpriteDrawOrder(ScratchSprite& s) :
        DrawOrder(s.get_x(), s.get_y(), DrawOrder::SPRITE), sprite(s) {}

    ScratchSprite& get_sprite() const { return sprite; }

private:
    ScratchSprite& sprite;
};