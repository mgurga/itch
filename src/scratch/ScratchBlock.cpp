#include "ScratchBlock.hpp"

ScratchBlock::ScratchBlock(json sb, std::string id):
    array_block(ScratchArrayBlock())
{
    if (sb.is_array()) {
        this->is_array_block = true;
        this->array_block = ScratchArrayBlock(sb, id);
    } else {
        this->is_array_block = false;
        this->id = id;
        this->opcode = sb["opcode"];
        this->next = sb["next"].is_null() ? "" : sb["next"];
        this->parent = sb["parent"].is_null() ? "" : sb["parent"];
        this->inputs = sb["inputs"];
        this->fields = sb["fields"];
        this->shadow = sb["shadow"];
        this->topLevel = sb["topLevel"];
        this->x = sb["x"].is_null() ? 0 : sb["x"].get<int>();
        this->y = sb["y"].is_null() ? 0 : sb["y"].get<int>();
    }
}