#include "ScratchBlock.hpp"

ScratchBlock::ScratchBlock(json sb, std::string id) : array_block(ScratchArrayBlock()) {
    if (sb.is_array()) {
        this->is_array_block = true;
        this->array_block = ScratchArrayBlock(sb, id);
        if (this->array_block.type == BlockType::VariableType) {
            this->opcode = "variable";
            this->x = array_block.x;
            this->y = array_block.y;
        } else if (this->array_block.type == BlockType::ListType) {
            this->opcode = "list";
            this->x = array_block.x;
            this->y = array_block.y;
        }
    } else {
        this->is_array_block = false;
        this->id = id;
        this->opcode = sb["opcode"];
        this->next = sb["next"].is_null() ? "" : sb["next"];
        this->parent = sb["parent"].is_null() ? "" : sb["parent"];
        this->inputs = sb["inputs"];
        this->fields = sb["fields"];
        if (sb.contains("mutation")) this->mutations = sb["mutation"];
        this->shadow = sb["shadow"];
        this->topLevel = sb["topLevel"];
        this->x = sb["x"].is_null() ? 0 : sb["x"].get<int>();
        this->y = sb["y"].is_null() ? 0 : sb["y"].get<int>();
    }
}