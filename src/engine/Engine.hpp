#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <variant>
#include <vector>

#include "../Project.hpp"
#include "../blocks/Link.hpp"
#include "../player/PlayerInfo.hpp"
#include "List.hpp"
#include "SpriteMessage.hpp"
#include "Variable.hpp"

namespace EngineFunctions {
class Engine {
public:
    Engine() : TOTAL_CHAINS(0){};
    Engine(Project& project);

    unsigned int TOTAL_CHAINS;
    bool finished = false;
    std::chrono::time_point<std::chrono::steady_clock> timer =
        std::chrono::high_resolution_clock::now();

    void tick(PlayerInfo* player_info);
    bool process_chain(Chain& c, ScratchSprite* s, bool force_activate = false);
    void process_link(Link& link, Chain& chain, ScratchSprite* sprite, int& i);
    Value compute_input(LinkInput block, ScratchSprite* sprite);
    Value compute_reporter(std::string opid, ScratchSprite* sprite);
    Value compute_condition(std::string opid, ScratchSprite* sprite);

    // utility functions
    Variable& get_var_by_name(std::string name);
    List& get_list_by_name(std::string name);
    Link get_reporter_by_id(std::string id);
    Link& get_link_by_id(std::string id);
    std::string variant_str(std::variant<std::string, double> varient);
    Chain& get_chain_by_link_id(std::string id, ScratchSprite* s);

    std::vector<Variable> variables;
    std::vector<List> lists;
    std::vector<Link> reporters;
    std::vector<Link> links;
    std::vector<std::string> broadcasts;
    std::vector<std::string> queued_broadcasts;
    std::vector<SpriteMessage> say_logs;

    Project* prj;
    PlayerInfo* pi;

    // motion helpers
    void move_steps(double steps, ScratchSprite* s);
    void go_to_menu(Link link, ScratchSprite* s);

    // control helpers
    void wait(double duration, Chain& c, int& i);
    void forever_loop(Link link, Chain& c, ScratchSprite* s, int& i);
    void stop_menu(Link link, Chain& c, ScratchSprite* s, int& i);
    void if_statement(Link link, ScratchSprite* s);
    void if_else_statement(Link link, ScratchSprite* s);
    void repeat_loop(Link link, Chain& c, ScratchSprite* s, int& i);

    // looks helpers
    void say(Link link, ScratchSprite* s);
    void say_for_sec(Link link, ScratchSprite* s, Chain& c, int& i);
    void switch_costume_to(Link link, ScratchSprite* s);
    void next_costume(ScratchSprite* s);

private:
    static unsigned int count_chains(Project& project);
};
}  // namespace EngineFunctions