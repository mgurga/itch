#include "Engine.hpp"

unsigned int EngineFunctions::Engine::count_chains(Project& project) {
    unsigned int totalchains = 0;
    totalchains += project.stage.chains.size();
    for (ScratchSprite& ss : project.sprites) {
        totalchains += ss.chains.size();
    }
    std::cout << "project contains " << totalchains << " chains" << std::endl;
    return totalchains;
}

ScratchBlock EngineFunctions::Engine::get_sb_by_id(std::string id) {
    for (ScratchBlock sb : prj->stage.blocks)
        if (sb.id == id)
            return sb;

    for (ScratchSprite ss : prj->sprites)
        for (ScratchBlock sb : ss.blocks)
            if (sb.id == id)
                return sb;

    throw std::invalid_argument("ScratchBlock with id '" + id + "' not found");
}

Variable& EngineFunctions::Engine::get_var_by_name(std::string name) {
    for (Variable& var : variables)
        if (var.name == name)
            return var;
    throw std::invalid_argument("variable '" + name + "' not found");
}

Link EngineFunctions::Engine::get_operator_by_id(std::string id) {
    for (Link& op : operators)
        if (op.block_id == id)
            return op;
    throw std::invalid_argument("operator with id '" + id + "' not found");
}

std::string EngineFunctions::Engine::variant_str(std::variant<std::string, double> varient) {
    if (std::holds_alternative<double>(varient)) {
        return std::to_string(std::get<double>(varient));
    } else if (std::holds_alternative<std::string>(varient)) {
        return std::get<std::string>(varient);
    } else {
        return "";
    }
}

Chain& EngineFunctions::Engine::get_chain_by_link_id(std::string id, ScratchSprite* s) {
    for (Chain& gc : s->chains)
        if (gc.links.at(0).block_id == id)
            return gc;
    throw std::invalid_argument("chain with beginning link id '" + id + "' not found");
}