#include "ScratchSprite.hpp"

ScratchSprite::ScratchSprite(json ss, std::string temp_dir, bool heavyload):
    ScratchTarget(ss, temp_dir, heavyload),
    x(ss["x"]),
    y(ss["y"]),
    size(ss["size"]),
    direction(ss["direction"]),
    draggable(ss["draggable"])
{
    if (ss["rotationStyle"] == "all around") {
        rotationStyle = ALL_AROUND;
    } else if (ss["rotationStyle"] == "left-right") {
        rotationStyle = LEFT_RIGHT;
    } else if (ss["rotationStyle"] == "don't rotate") {
        rotationStyle = DONT_ROTATE;
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
    rotationStyle(ALL_AROUND)
{}