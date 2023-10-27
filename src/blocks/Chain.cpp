#include "Chain.hpp"

std::vector<Chain> Chain::create_chains(std::vector<ScratchBlock> blocks) {
    std::vector<Chain> out;

    auto by_id = [&](std::string id) -> ScratchBlock {
        for (ScratchBlock b : blocks)
            if (b.id == id) return b;
        throw std::invalid_argument("ScratchBlock with id '" + id +
                                    "' not found when creating chains");
    };

    std::vector<std::string> start_ids;
    for (ScratchBlock b : blocks) {
        OPCODE bop = Opcodes::opcode_to_enum(b.opcode);
        bool createchain = false;

        if (bop == OPCODE::DEFINITION) start_ids.push_back(b.id);
        if ((OPCODE::WHEN_FLAG_CLICKED <= bop && bop <= OPCODE::WHEN_BROADCAST_RECEIVED) ||
            bop == OPCODE::START_AS_CLONE)
            start_ids.push_back(b.id);
        if (bop == OPCODE::FOREVER && !b.inputs.empty() && !b.inputs["SUBSTACK"][1].is_null())
            start_ids.push_back(b.inputs["SUBSTACK"][1]);
        if (bop == OPCODE::IF && !b.inputs.empty()) {
            if (b.inputs.contains("CONDITION")) start_ids.push_back(b.inputs["CONDITION"][1]);
            if (b.inputs.contains("SUBSTACK") && !b.inputs["SUBSTACK"][1].is_null())
                start_ids.push_back(b.inputs["SUBSTACK"][1]);
        }
        if (bop == OPCODE::IF_ELSE && !b.inputs.empty()) {
            if (b.inputs.contains("CONDITION")) start_ids.push_back(b.inputs["CONDITION"][1]);
            if (b.inputs.contains("SUBSTACK") && !b.inputs["SUBSTACK"][1].is_null())
                start_ids.push_back(b.inputs["SUBSTACK"][1]);
            if (b.inputs.contains("SUBSTACK2") && !b.inputs["SUBSTACK2"][1].is_null())
                start_ids.push_back(b.inputs["SUBSTACK2"][1]);
        }
        if (bop == OPCODE::REPEAT && !b.inputs.empty()) {
            if (b.inputs.contains("SUBSTACK") && !b.inputs["SUBSTACK"][1].is_null())
                start_ids.push_back(b.inputs["SUBSTACK"][1]);
        }
    }

    Chain* tempchain;
    for (std::string sid : start_ids) {
        ScratchBlock b = by_id(sid);
        tempchain = new Chain();
        Link l = Link(b);
        tempchain->add_link(l);
        tempchain->activatable = (OPCODE::WHEN_FLAG_CLICKED <= l.opcode &&
                                  l.opcode <= OPCODE::WHEN_BROADCAST_RECEIVED) ||
                                 l.opcode == OPCODE::START_AS_CLONE;

        ScratchBlock curBlock = b;
        while (curBlock.next != "") {
            curBlock = by_id(curBlock.next);
            tempchain->add_link(Link(curBlock));
        }

        out.push_back(*tempchain);
        delete tempchain;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const Chain& c) {
    if (c.links.size() == 0) {
        out << "chain has no links" << std::endl;
        return out;
    }

    out << c.links[0].string_opcode << std::endl;
    for (int i = 1; i < c.links.size(); i++) {
        out << "L " << c.links[i].string_opcode << std::endl;
    }

    return out;
};