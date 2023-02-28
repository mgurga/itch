#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum BlockType {
    Uninitialized = 0,
    Number = 4,
    Positive_Number = 5,
    Positive_Integer = 6,
    Integer = 7,
    Angle = 8,
    Color = 9,
    String = 10,
    Broadcast = 11,
    Variable = 12,
    List = 13
};

class ScratchArrayBlock {
public:
    ScratchArrayBlock() { type = Uninitialized; }
    ScratchArrayBlock(json sb, std::string id) {
        type = static_cast<BlockType>(sb[0]);
        block_id = id;

        switch (type) {
        case Number: case Positive_Integer: case Positive_Number: case Integer: case Angle:
            num_val = sb[1];
            break;
        case Color: case String:
            str_value = sb[1];
            break;
        case Broadcast:
            str_value = sb[1];
            element_id = sb[2];
            break;
        case Variable: case List:
            str_value = sb[1];
            element_id = sb[2];
            x = sb[3];
            y = sb[4];
            break;
        default:
            break;
        }
    }

    std::string block_id;

    BlockType type;
    int num_val;
    std::string str_value;
    std::string element_id;
    int x, y;
};
