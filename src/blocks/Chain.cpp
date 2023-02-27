#include "Chain.hpp"

Chain::Chain() {

}

std::vector<Chain> Chain::create_chains(std::vector<ScratchBlock> blocks) {
    std::vector<Chain> out;

    Chain tempchain;
    for (ScratchBlock b : blocks) {
        if (b.next != "") {
            tempchain.links.push_back(Link(b));
        } else {
            out.push_back(tempchain);
            tempchain.links.clear();
        }
    }

    return out;
}