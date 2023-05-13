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
    std::chrono::high_resolution_clock::time_point timer =
        std::chrono::high_resolution_clock::now();
    int fronts = 0;
    int backs = 0;

    void tick(PlayerInfo* player_info);
    bool process_chain(Chain& c, ScratchTarget* s, bool force_activate = false);
    void process_link(Link& link, Chain& chain, ScratchTarget* sprite, int& i);
    Value compute_input(LinkInput block, ScratchTarget* sprite);
    Value compute_reporter(std::string opid, ScratchTarget* sprite);
    Value compute_condition(std::string opid, ScratchTarget* sprite);

    // utility functions
    Variable& get_var_by_name(std::string name);
    List& get_list_by_name(std::string name);
    Link get_reporter_by_id(std::string id);
    Link& get_link_by_id(std::string id);
    std::string variant_str(std::variant<std::string, double> varient);
    Chain& get_chain_by_link_id(std::string id, ScratchTarget* s);
    ScratchTarget& get_target_by_name(std::string name);

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
    void move_steps(double steps, ScratchTarget* s);
    void go_to_menu(Link link, ScratchTarget* s);

    // control helpers
    void wait(double duration, Chain& c, int& i);
    void forever_loop(Link link, Chain& c, ScratchTarget* s, int& i);
    void stop_menu(Link link, Chain& c, ScratchTarget* s, int& i);
    void if_statement(Link link, ScratchTarget* s);
    void if_else_statement(Link link, ScratchTarget* s);
    void repeat_loop(Link link, Chain& c, ScratchTarget* s, int& i);

    // looks helpers
    void say(Link link, ScratchTarget* s);
    void say_for_sec(Link link, ScratchTarget* s, Chain& c, int& i);
    void switch_costume_to(Link link, ScratchTarget* s);
    void next_costume(ScratchTarget* s);
    void go_to_layer(std::string fb, ScratchTarget* s);
    void change_layer_by(Link link, ScratchTarget* s);

private:
    static unsigned int count_chains(Project& project);
};
}  // namespace EngineFunctions