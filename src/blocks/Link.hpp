#pragma once

#include <string>

#include "../scratch/ScratchBlock.hpp"
#include "Chain.hpp"
#include "Opcodes.hpp"

class Link {
public:
    Link(ScratchBlock b):
        string_opcode(b.opcode),
        opcode(Opcodes::opcode_to_enum(b.opcode)),
        inputs(b.inputs),
        fields(b.fields),
        block_id(b.id)
    {}

    std::string block_id;
    OPCODE opcode;
    std::string string_opcode;
    json inputs;
    json fields;
};