#include "Chain.hpp"

std::vector<Chain> Chain::create_chains(std::vector<ScratchBlock> blocks) {
    std::vector<Chain> out;

    auto by_id = [&] (std::string id) -> ScratchBlock {
        for (ScratchBlock b : blocks)
            if (b.id == id)
                return b;
        return ScratchBlock();
    };

    Chain* tempchain;
    for (ScratchBlock b : blocks) {
        OPCODE bop = Opcodes::opcode_to_enum(b.opcode);
        if (WHEN_FLAG_CLICKED <= bop && bop <= WHEN_BROADCAST_RECEIVED) {
            tempchain = new Chain();
            tempchain->links.push_back(Link(b));
            tempchain->activatable = true;

            ScratchBlock curBlock = b;
            while(curBlock.next != "") {
                curBlock = by_id(curBlock.next);
                tempchain->links.push_back(Link(curBlock));
            }

            if (curBlock.next == "") {
                out.push_back(*tempchain);
                delete tempchain;
            }
        }
    }

    return out;
}

std::ostream& operator<<(std::ostream &out, const Chain& c) {
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