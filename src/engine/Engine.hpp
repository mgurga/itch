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
#include "GlideProgress.hpp"
#include "List.hpp"
#include "SpriteMessage.hpp"
#include "Variable.hpp"

namespace EngineFunctions {

static const double PI = std::acos(-1);  // TODO: Use std::numbers::pi in C++20

class Engine {
public:
    Engine() : TOTAL_CHAINS(0){};
    Engine(Project& project);

    unsigned int TOTAL_CHAINS;
    bool finished = false;
    bool processing_clones = false;
    std::chrono::high_resolution_clock::time_point timer =
        std::chrono::high_resolution_clock::now();
    int fronts = 0;
    int backs = 0;

    void tick(PlayerInfo* player_info);
    bool process_chain(Chain& c, ScratchTarget* s, bool force_activate = false);
    void process_link(Link& link, Chain& chain, ScratchTarget* sprite, int& i);
    Value compute_input(LinkInput block, ScratchTarget* sprite);
    Value compute_reporter(Link op, ScratchTarget* sprite = nullptr);
    Value compute_condition(Link op, ScratchTarget* sprite);

    // utility functions
    Variable& get_var_by_name(std::string name);
    Variable& get_proc_var_by_name(std::string name);
    List& get_list_by_name(std::string name);
    Link& get_link_by_id(std::string id);
    std::string variant_str(std::variant<std::string, double> varient);
    Chain& get_chain_by_link_id(std::string id, ScratchTarget* s);
    ScratchTarget& get_target_by_name(std::string name);

    std::vector<Variable> variables;
    std::vector<Variable> procedure_variables;
    std::vector<List> lists;
    std::vector<Link> links;
    std::vector<std::string> broadcasts;
    std::vector<std::string> queued_broadcasts;
    std::vector<SpriteMessage> say_logs;
    std::vector<ScratchSprite> clones;
    std::vector<GlideProgress> glide_progresses;

    Project* prj;
    PlayerInfo* pi;

    // motion helpers
    void move_steps(double steps, ScratchTarget* s);
    void go_to_menu(Link link, ScratchTarget* s);
    void set_rotation_style(std::string rs, ScratchTarget* s);
    void glide_for_secs(Link link, ScratchTarget* s, Chain& c, int& i);

    // control helpers
    void wait(double duration, Chain& c, int& i);
    void forever_loop(Link link, Chain& c, ScratchTarget* s, int& i);
    void stop_menu(Link link, Chain& c, ScratchTarget* s, int& i);
    void if_statement(Link link, ScratchTarget* s);
    void if_else_statement(Link link, ScratchTarget* s);
    void repeat_loop(Link link, Chain& c, ScratchTarget* s, int& i);
    void create_clone_of(Link link, ScratchTarget* s);

    // looks helpers
    void say(Link link, ScratchTarget* s);
    void say_for_sec(Link link, ScratchTarget* s, Chain& c, int& i);
    void switch_costume_to(Link link, ScratchTarget* s);
    void next_costume(ScratchTarget* s);
    void go_to_layer(std::string fb, ScratchTarget* s);
    void change_layer_by(Link link, ScratchTarget* s);
    void change_effect_by(Link link, ScratchTarget* s);

    // procedure helper
    void call_procedure(Link link, ScratchTarget* s);

private:
    static unsigned int count_chains(Project& project);
};
}