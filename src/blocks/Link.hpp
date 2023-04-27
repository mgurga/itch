#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "../scratch/ScratchArrayBlock.hpp"
#include "../scratch/ScratchBlock.hpp"
#include "LinkInput.hpp"
#include "Opcodes.hpp"

class Link {
public:
    Link(ScratchBlock b) :
        string_opcode(b.opcode), opcode(Opcodes::opcode_to_enum(b.opcode)), id(b.id) {
        for (auto fl : b.fields.items()) {
            for (auto v : fl.value())
                if (!v.is_null()) fields[std::string(fl.key())].push_back(v.get<std::string>());
        }

        for (auto in : b.inputs.items()) {
            if (in.value()[1].is_string()) {
                ScratchArrayBlock sab;
                sab.type = BlockType::Uninitialized;
                sab.str_value = in.value()[1];
                inputs[in.key()] = LinkInput(in.value()[0], sab);
            } else {
                inputs[in.key()] = LinkInput(in.value()[0], ScratchArrayBlock(in.value()[1]));
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Link link) {
        os << "Link: { ";
        os << "string_opcode: " << link.string_opcode << " ";
        os << "inputs: ";
        for (auto& kv : link.inputs) os << "Input { " << kv.first << ": " << kv.second.sab << "} ";
        os << "fields: ";
        for (auto& kv : link.fields) {
            os << "Field { " << kv.first << ": ";
            for (std::string s : kv.second) { os << s << ", "; }
            os << " }";
        }
        return os;
    }

    bool inputs_contains(std::string s) { return !(inputs.find(s) == inputs.end()); }

    std::string id;
    OPCODETYPE opcode;
    std::string string_opcode;
    std::map<std::string, std::vector<std::string>> fields;
    std::map<std::string, LinkInput> inputs;
};