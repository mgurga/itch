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
#include "../DebugMacros.hpp"
#include "../blocks/Link.hpp"
#include "../blocks/Opcodes.hpp"
#include "SpriteMessage.hpp"
#include "Variable.hpp"
#include "List.hpp"

namespace EngineFunctions {
class Engine {
public:
    Engine(): TOTAL_CHAINS(0) {};
    Engine(Project& project);

    unsigned int TOTAL_CHAINS;
    bool finished = false;

    void tick(PlayerInfo* player_info);
    bool process_chain(Chain& c, ScratchSprite* s, bool force_activate = false);
    void process_link(Link& link, Chain& chain, ScratchSprite* sprite, int& i);
    Value compute_input(json block);
    std::variant<std::string, double> compute_operator(std::string opid);
    bool compute_condition(std::string opid);

    // utility functions
    Variable& get_var_by_name(std::string name);
    List& get_list_by_name(std::string name);
    Link get_operator_by_id(std::string id);
    ScratchBlock get_sb_by_id(std::string id);
    std::string variant_str(std::variant<std::string, double> varient);
    Chain& get_chain_by_link_id(std::string id, ScratchSprite* s);

    std::vector<Variable> variables;
    std::vector<List> lists;
    std::vector<Link> operators;
    std::vector<std::string> broadcasts;
    std::vector<std::string> queued_broadcasts;
    std::vector<SpriteMessage> say_logs;

    Project* prj;
    PlayerInfo* pi;

    // motion helpers
    void move_steps(Link link, ScratchSprite* s);
    void go_to_menu(Link link, ScratchSprite* s);

    // control helpers
    void wait(double duration, Chain& c, int& i);
    void forever_loop(Link link, Chain& c, ScratchSprite* s, int& i);
    void stop_menu(Link link, Chain& c, ScratchSprite* s, int& i);
    void if_statement(Link link, ScratchSprite* s);
    void if_else_statement(Link link, ScratchSprite* s);

    // looks helpers
    void say(Link link, ScratchSprite* s);
    void say_for_sec(Link link, ScratchSprite* s, Chain& c, int& i);
    void switch_costume_to(Link link, ScratchSprite* s);
    void next_costume(ScratchSprite* s);
private:
    static unsigned int count_chains(Project& project);
};
}