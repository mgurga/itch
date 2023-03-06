#pragma once

#include <string>
#include "../scratch/ScratchBlock.hpp"
#include "Opcodes.hpp"

class Link {
public:
    Link(ScratchBlock b) {
        opcode = Opcodes::opcode_to_enum(b.opcode);
        string_opcode = b.opcode;
    }

    OPCODE opcode;
    std::string string_opcode;
};