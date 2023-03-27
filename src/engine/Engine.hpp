#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <variant>
#include <cmath>
#include <chrono>

#include "../player/PlayerInfo.hpp"
#include "../Project.hpp"
#include "../blocks/Link.hpp"
#include "../blocks/Opcodes.hpp"
#include "Variable.hpp"

namespace EngineFunctions {
class Engine {
public:
    Engine(): TOTAL_CHAINS(0) {};
    Engine(Project& project);

    unsigned int TOTAL_CHAINS;
    bool finished = false;

    void tick(Project& project, PlayerInfo* player_info);
    bool process_chain(Chain& c, ScratchSprite* s);
    void process_link(Link& link, Chain& chain, ScratchSprite* sprite, int& i);
    std::variant<std::string, double> compute_input(json block);
    std::variant<std::string, double> compute_operator(std::string opid);

    Variable& get_var_by_name(std::string name);
    Link get_operator_by_id(std::string id);
    ScratchBlock get_sb_by_id(std::string id);
    std::string variant_str(std::variant<std::string, double> varient);

    std::vector<Variable> variables;
    std::vector<Link> operators;
    std::vector<std::string> broadcasts;
    std::vector<std::string> queued_broadcasts;

    Project* prj;
    PlayerInfo* pi;

    void move_steps(Link link, ScratchSprite* s);
    void go_to_menu(Link link, ScratchSprite* s);

    void wait(double duration, Chain& c, int& i);
    void forever_loop(Link link, Chain& c, ScratchSprite* s, int& i);
    void stop_menu(Link link, Chain& c, ScratchSprite* s, int& i);

private:
    static unsigned int count_chains(Project& project);
};
}