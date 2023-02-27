#pragma once

#include <string>
#include <vector>
#include "../scratch/ScratchBlock.hpp"
#include "Block.hpp"

class Link {
public:
    Link(ScratchBlock b);

    OPCODE opcode;
    ScratchBlock &block;
};