#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "ScratchTarget.hpp"
#include "ScratchStage.hpp"

enum RotationStyle {
    ALL_AROUND,
    LEFT_RIGHT,
    DONT_ROTATE
};

class ScratchSprite : public ScratchTarget {
public:
    ScratchSprite(json ss, std::string temp_dir, bool heavyload = true);
    ScratchSprite(ScratchStage& st);

    bool visible;
    int x, y, size, direction;
    bool draggable;
    RotationStyle rotationStyle;
};