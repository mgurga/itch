#include "Link.hpp"

Link::Link(ScratchBlock b): block(b) {
    opcode = Block::opcode_to_enum(block.opcode);
}