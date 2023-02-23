#include "ScratchBlock.hpp"

ScratchBlock::ScratchBlock(json sb, std::string id):
    id(id),
    opcode(sb["opcode"]),
    next(sb["next"].is_null() ? "" : sb["next"]),
    parent(sb["parent"].is_null() ? "" : sb["parent"]),
    inputs(sb["inputs"]),
    fields(sb["fields"]),
    shadow(sb["shadow"]),
    topLevel(sb["topLevel"]),
    x(sb["x"].is_null() ? 0 : sb["x"]),
    y(sb["y"].is_null() ? 0 : sb["y"])
{}