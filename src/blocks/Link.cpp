#include "Link.hpp"

Link::Link(std::string opcode, std::string next, std::string parent):
    opcode(opcode),
    next(next),
    parent(parent)
{}