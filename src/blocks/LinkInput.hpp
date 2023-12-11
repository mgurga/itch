#pragma once

#include <optional>
#include <sstream>
#include <string>

#include "../scratch/ScratchArrayBlock.hpp"

struct ShadowArrayBlock {
    int shadow;
    ScratchArrayBlock sab;

    friend std::ostream& operator<<(std::ostream& os, ShadowArrayBlock sab) {
        os << "ShadowArrayBlock { shadow: " << sab.shadow
           << ", ScratchArrayBlock: { blocktype: " << static_cast<int>(sab.sab.type)
           << ", num_val: " << sab.sab.num_val << ", str_val: " << sab.sab.str_value << " }";
        return os;
    }

    operator int() { return shadow; }
    operator ScratchArrayBlock() { return sab; }
    operator std::string() { return sab.str_value; }
};

class LinkInput {
public:
    LinkInput() {}
    LinkInput(std::string rid) { reporter_id = rid; }
    LinkInput(int s, ScratchArrayBlock sab) : sab({s, sab}) {
        if (sab.type == BlockType::Uninitialized)
            reporter_id = sab.str_value;
        else
            reporter_id = {};
    }
    LinkInput(ShadowArrayBlock sab) : LinkInput(sab.shadow, sab.sab) {}

    ShadowArrayBlock sab;
    std::optional<std::string> reporter_id;

    ShadowArrayBlock operator[](int num) { return sab; }
};