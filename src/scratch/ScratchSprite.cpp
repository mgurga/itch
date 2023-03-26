#include "ScratchSprite.hpp"

ScratchSprite::ScratchSprite(json ss, std::filesystem::path temp_dir, bool heavyload):
    ScratchTarget(ss, temp_dir, heavyload),
    x(ss["x"]),
    y(ss["y"]),
    size(ss["size"]),
    direction(ss["direction"]),
    draggable(ss["draggable"]),
    visible(ss["visible"])
{
    if (ss["rotationStyle"] == "all around") {
        rotationStyle = RotationStyle::ALL_AROUND;
    } else if (ss["rotationStyle"] == "left-right") {
        rotationStyle = RotationStyle::LEFT_RIGHT;
    } else if (ss["rotationStyle"] == "don't rotate") {
        rotationStyle = RotationStyle::DONT_ROTATE;
    } else {
        rotationStyle = ALL_AROUND;
    }
}

ScratchSprite::ScratchSprite(ScratchStage& ss):
    ScratchTarget(),
    x(0),
    y(0),
    size(100),
    direction(90),
    draggable(false),
    rotationStyle(ALL_AROUND),
    visible(true)
{}