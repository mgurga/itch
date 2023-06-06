#include "Engine.hpp"

unsigned int EngineFunctions::Engine::count_chains(Project& project) {
    unsigned int totalchains = 0;
    totalchains += project.stage.chains.size();
    for (ScratchSprite& ss : project.sprites) { totalchains += ss.chains.size(); }
    std::cout << "project contains " << totalchains << " chains" << std::endl;
    return totalchains;
}

Link& EngineFunctions::Engine::get_link_by_id(std::string id) {
    for (Link& l : links)
        if (l.id == id) return l;
    throw std::invalid_argument("Link with id '" + id + "' not found");
}

Variable& EngineFunctions::Engine::get_var_by_name(std::string name) {
    for (Variable& var : variables)
        if (var.name == name) return var;
    throw std::invalid_argument("variable '" + name + "' not found");
}

List& EngineFunctions::Engine::get_list_by_name(std::string name) {
    for (List& list : lists)
        if (list.name == name) return list;
    throw std::invalid_argument("list '" + name + "' not found");
}

Link EngineFunctions::Engine::get_reporter_by_id(std::string id) {
    for (Link& op : reporters)
        if (op.id == id) return op;
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

Chain& EngineFunctions::Engine::get_chain_by_link_id(std::string id, ScratchTarget* s) {
    for (Chain& gc : s->chains)
        if (gc.links.at(0).id == id) return gc;
    throw std::invalid_argument("chain with beginning link id '" + id + "' not found");
}

ScratchTarget& EngineFunctions::Engine::get_target_by_name(std::string name) {
    if (name == "Stage") return prj->stage;
    for (ScratchTarget& t : prj->sprites)
        if (t.get_name() == name) return t;
    throw std::invalid_argument("target with name '" + name + "' not found");
}