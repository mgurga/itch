#include "Engine.hpp"

EngineFunctions::Engine::Engine(Project& project) :
    TOTAL_CHAINS(count_chains(project)), prj(&project) {
    for (ScratchVariable sv : project.stage.variables) variables.push_back(sv);
    for (ScratchList sl : project.stage.lists) lists.push_back(sl);
    for (Link l : project.stage.links) links.push_back(l);

    for (ScratchSprite sprite : project.sprites) {
        for (ScratchVariable sv : sprite.variables) {
            Variable newvar = Variable(sv);
            newvar.make_local(sprite.name());
            variables.push_back(newvar);
        }
        for (ScratchList sl : sprite.lists) {
            List newlist = List(sl);
            newlist.make_local(sprite.name());
            lists.push_back(newlist);
        }
        for (Link l : sprite.links) links.push_back(l);
    }

    std::cout << "initialized " << variables.size() << " variable(s)" << std::endl;
    for (Variable v : variables) { std::cout << "'" << v.name << "', "; }
    std::cout << std::endl;

    std::cout << "initialized " << lists.size() << " list(s)" << std::endl;
    for (List l : lists) { std::cout << "'" << l.name << "', "; }
    std::cout << std::endl;

    for (ScratchBlock& b : project.stage.blocks) {
        OPCODETYPE bop = Opcodes::opcode_to_enum(b.opcode);
        if (bop == OPTYPE::REPORTER) reporters.push_back(b);
    }

    for (ScratchSprite& sprite : project.sprites) {
        for (ScratchBlock& b : sprite.blocks) {
            OPCODETYPE bop = Opcodes::opcode_to_enum(b.opcode);
            if (bop == OPTYPE::REPORTER) reporters.push_back(b);
        }
    }

    std::cout << "found " << reporters.size() << " reporters(s)" << std::endl;
    std::cout << "finished initializing engine" << std::endl;
}

void EngineFunctions::Engine::tick(PlayerInfo* player_info) {
    if (finished) return;
    broadcasts = queued_broadcasts;
    queued_broadcasts.clear();

    pi = player_info;

    // delete old messages
    auto cur = std::chrono::high_resolution_clock::now();
    say_logs.erase(std::remove_if(say_logs.begin(), say_logs.end(),
                                  [&cur](SpriteMessage sm) { return (sm.end_time <= cur); }),
                   say_logs.end());

    int processed_chains = 0;
    // hack to treat ScratchStage as a ScratchSprite
    for (Chain& chain : prj->stage.chains) {
        if (process_chain(chain, dynamic_cast<ScratchTarget*>(&prj->stage))) { processed_chains++; }
    }

    for (ScratchSprite& sprite : prj->sprites) {
        for (Chain& chain : sprite.chains) {
            if (process_chain(chain, &sprite)) { processed_chains++; }
        }
    }

    broadcasts.clear();

    if (processed_chains == 0) {
        std::cout << "project is finished running" << std::endl;
        finished = true;
    }
}

Value EngineFunctions::Engine::compute_input(LinkInput input, ScratchTarget* sprite) {
    if (input.reporter_id.has_value()) return compute_reporter(input.reporter_id.value(), sprite);

    ScratchArrayBlock sab = input.sab.sab;

    if (sab.type >= BlockType::Number && sab.type <= BlockType::Angle) return Value(sab.num_val);
    if (sab.type >= BlockType::Color && sab.type <= BlockType::Broadcast)
        return Value(sab.str_value);
    if (sab.type == BlockType::VariableType) return get_var_by_name(sab.str_value).val();
    return Value("");
}

bool EngineFunctions::Engine::process_chain(Chain& chain, ScratchTarget* s, bool force_activate) {
    if ((chain.activatable || !chain.continue_at.empty()) || force_activate) {
        // used to interrupt continue_at if WHEN_KEY_CLICKED, BROADCAST_RECIEVED, or other special
        // events activate
        if (chain.links.at(0).opcode >= WHEN_FLAG_CLICKED &&
            chain.links.at(0).opcode <= BROADCAST_AND_WAIT) {
            int init_link = 0;
            process_link(chain.links.at(0), chain, s, init_link);
        }

        // resume i to continue_at if set
        int start_link = 0;
        if (!chain.continue_at.empty()) start_link = chain.continue_at.back().link_num;

        // process all other links in chain
        for (int i = start_link; i < chain.links.size(); i++) {
            process_link(chain.links.at(i), chain, s, i);
            if (i == -1) break;
        }
        return true;
    }
    return false;
}

void EngineFunctions::Engine::process_link(Link& link, Chain& c, ScratchTarget* s, int& i) {
    // std::cout << "processing link opcode: " << link.string_opcode << std::endl;
    if (s == nullptr) {
        // throw std::invalid_argument("scratch sprite pointer is null when processing link");
        std::cout << "scratch sprite pointer is null when processing link with opcode "
                  << link.string_opcode << std::endl;
        return;
    }

    switch (link.opcode.opcode) {
    // Variables
    case OPCODE::SET_VARIABLE_TO:
        get_var_by_name(link.fields["VARIABLE"][0]) = compute_input(link.inputs["VALUE"], s);
        break;
    case OPCODE::CHANGE_VARIABLE_BY:
        get_var_by_name(link.fields["VARIABLE"][0]) +=
            compute_input(link.inputs["VALUE"], s).get_number();
        break;
    case OPCODE::DELETE_ALL: get_list_by_name(link.fields["LIST"][0]).delete_all(); break;
    case OPCODE::ADD_TO_LIST:
        get_list_by_name(link.fields["LIST"][0])
            .add_to_list(Value(compute_input(link.inputs["ITEM"], s)));
        break;
    case OPCODE::REPLACE_ITEM:
        get_list_by_name(link.fields["LIST"][0])
            .set(static_cast<int>(compute_input(link.inputs["INDEX"], s).get_number()),
                 compute_input(link.inputs["ITEM"], s));
        break;
    case OPCODE::INSERT_AT:
        get_list_by_name(link.fields["LIST"][0])
            .insert_at(static_cast<int>(compute_input(link.inputs["INDEX"], s).get_number()),
                       compute_input(link.inputs["ITEM"], s));
        break;

    // Events
    case OPCODE::WHEN_FLAG_CLICKED: c.activatable = false; break;
    case OPCODE::WHEN_KEY_PRESSED:
        if (!(std::find(pi->pressed.begin(), pi->pressed.end(), link.fields["KEY_OPTION"][0]) !=
              pi->pressed.end())) {
            i = -1;
        } else {
            c.continue_at.clear();
        }
        break;
    case OPCODE::WHEN_BROADCAST_RECEIVED:
        if (!(std::find(broadcasts.begin(), broadcasts.end(), link.fields["BROADCAST_OPTION"][0]) !=
              broadcasts.end())) {
            i = -1;
        } else {
            c.continue_at.clear();
        }
        break;
    case OPCODE::BROADCAST:
        queued_broadcasts.push_back(compute_input(link.inputs["BROADCAST_INPUT"], s).get_string());
        break;

    // Motion
    case OPCODE::GO_TO: go_to_menu(link, s); break;
    case OPCODE::SET_X_TO: s->x() = compute_input(link.inputs["X"], s); break;
    case OPCODE::SET_Y_TO: s->y() = compute_input(link.inputs["Y"], s); break;
    case OPCODE::CHANGE_Y_BY: s->y() += compute_input(link.inputs["DY"], s).get_number(); break;
    case OPCODE::CHANGE_X_BY: s->x() += compute_input(link.inputs["DX"], s).get_number(); break;
    case OPCODE::POINT_IN_DIRECTION:
        s->direction() = compute_input(link.inputs["DIRECTION"], s);
        break;
    case OPCODE::GO_TO_XY:
        s->x() = compute_input(link.inputs["X"], s);
        s->y() = compute_input(link.inputs["Y"], s);
        break;
    case OPCODE::TURN_LEFT:
        s->direction() -= compute_input(link.inputs["DEGREES"], s).get_number();
        break;
    case OPCODE::TURN_RIGHT:
        s->direction() += compute_input(link.inputs["DEGREES"], s).get_number();
        break;
    case OPCODE::MOVE_STEPS: move_steps(compute_input(link.inputs["STEPS"], s), s); break;

    // Control
    case OPCODE::WAIT: wait(compute_input(link.inputs["DURATION"], s).get_number(), c, i); break;
    case OPCODE::FOREVER: forever_loop(link, c, s, i); break;
    case OPCODE::STOP: stop_menu(link, c, s, i); break;
    case OPCODE::IF: if_statement(link, s); break;
    case OPCODE::IF_ELSE: if_else_statement(link, s); break;
    case OPCODE::REPEAT: repeat_loop(link, c, s, i); break;

    // Looks
    case OPCODE::SAY_FOR_SECS: say_for_sec(link, s, c, i); break;
    case OPCODE::SAY: say(link, s); break;
    case OPCODE::SHOW: s->visible() = true; break;
    case OPCODE::HIDE: s->visible() = false; break;
    case OPCODE::SWITCH_TO_COSTUME: switch_costume_to(link, s); break;
    case OPCODE::NEXT_COSTUME: next_costume(s); break;
    case OPCODE::SET_EFFECT_TO:
        s->effects()[link.fields["EFFECT"][0]] = compute_input(link.inputs["VALUE"], s);
        break;
    case OPCODE::CHANGE_EFFECT_BY:
        s->effects()[link.fields["EFFECT"][0]] +=
            compute_input(link.inputs["CHANGE"], s).get_number();
        break;
    case OPCODE::CLEAR_GRAPHIC_EFFECTS:
        s->effects() = {{"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
                        {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
        break;

    // Sensing
    case OPCODE::RESET_TIMER: timer = std::chrono::high_resolution_clock::now(); break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'"
                  << std::endl;
        break;
    }
}