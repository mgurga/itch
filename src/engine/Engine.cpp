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

    fronts = 0;
    backs = 0;

    pi = player_info;

    // delete old messages
    auto cur = std::chrono::high_resolution_clock::now();
    say_logs.erase(std::remove_if(say_logs.begin(), say_logs.end(),
                                  [&cur](SpriteMessage sm) { return (sm.end_time <= cur); }),
                   say_logs.end());

    int processed_chains = 0;
    processing_clones = false;
    // hack to treat ScratchStage as a ScratchSprite
    for (Chain& chain : prj->stage.chains) {
        if (process_chain(chain, dynamic_cast<ScratchTarget*>(&prj->stage))) { processed_chains++; }
    }

    for (ScratchSprite& sprite : prj->sprites) {
        for (Chain& chain : sprite.chains) {
            if (process_chain(chain, &sprite)) { processed_chains++; }
        }
    }

    // loop through clones and run their chains
    processing_clones = true;
    for (ScratchSprite& sprite : clones) {
        for (Chain& chain : sprite.chains) {
            if (process_chain(chain, &sprite)) { processed_chains++; }
        }
    }
    clones.erase(std::remove_if(clones.begin(), clones.end(),
                                [](ScratchSprite ss) { return ss.name() == ""; }),
                 clones.end());
    prj->clones = clones;

    broadcasts.clear();

    // sort sprites based on layer. very shortsided solution, will have to change later
    std::sort(prj->sprites.begin(), prj->sprites.end(),
              [](ScratchSprite& a, ScratchSprite& b) { return a.layerOrder() < b.layerOrder(); });

    // update monitor values
    for (ScratchMonitor& monitor : prj->monitors) {
        if (!monitor.visible) continue;
        ScratchTarget* target =
            monitor.spriteName == "" ? nullptr : &get_target_by_name(monitor.spriteName);
        if (monitor.opcode == "data_variable") {
            monitor.value = get_var_by_name(monitor.params["VARIABLE"]).val().get_string();
            monitor.display_name = monitor.params["VARIABLE"];
        } else if (monitor.opcode == "sensing_timer") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = "timer";
        } else if (monitor.opcode == "motion_xposition") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = monitor.spriteName + ": x position";
        } else if (monitor.opcode == "motion_yposition") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = monitor.spriteName + ": y position";
        } else if (monitor.opcode == "motion_direction") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = monitor.spriteName + ": direction";
        } else if (monitor.opcode == "sound_volume") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = "volume";
        } else if (monitor.opcode == "looks_size") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = monitor.spriteName + ": size";
        } else if (monitor.opcode == "sensing_username") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = "username";
        } else if (monitor.opcode == "sensing_loudness") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = "loudness";
        } else if (monitor.opcode == "sensing_answer") {
            monitor.value = compute_reporter(Link(monitor.opcode), target).get_string();
            monitor.display_name = "answer";
        } else if (monitor.opcode == "looks_costumenumbername") {
            if (monitor.params["NUMBER_NAME"] == "number") {
                Link l(monitor.opcode);
                l.fields["NUMBER_NAME"].push_back("number");
                monitor.value = compute_reporter(l, target).get_string();
                monitor.display_name = monitor.spriteName + ": costume number";
            } else {
                Link l(monitor.opcode);
                l.fields["NUMBER_NAME"].push_back("name");
                monitor.value = compute_reporter(l, target).get_string();
                monitor.display_name = monitor.spriteName + ": costume name";
            }
        } else if (monitor.opcode == "looks_backdropnumbername") {
            if (monitor.params["NUMBER_NAME"] == "number") {
                Link l(monitor.opcode);
                l.fields["NUMBER_NAME"].push_back("number");
                monitor.value = compute_reporter(l, target).get_string();
                monitor.display_name = "backdrop number";
            } else {
                Link l(monitor.opcode);
                l.fields["NUMBER_NAME"].push_back("name");
                monitor.value = compute_reporter(l, target).get_string();
                monitor.display_name = "backdrop name";
            }
        } else if (monitor.opcode == "sensing_current") {
            Link l(monitor.opcode);
            l.fields["CURRENTMENU"].push_back(monitor.params["CURRENTMENU"]);
            monitor.value = compute_reporter(l, target).get_string();
            if (monitor.params["CURRENTMENU"] == "YEAR") monitor.display_name = "year";
            if (monitor.params["CURRENTMENU"] == "MONTH") monitor.display_name = "month";
            if (monitor.params["CURRENTMENU"] == "DAYOFWEEK") monitor.display_name = "day of week";
            if (monitor.params["CURRENTMENU"] == "HOUR") monitor.display_name = "hour";
            if (monitor.params["CURRENTMENU"] == "SECOND") monitor.display_name = "second";
            if (monitor.params["CURRENTMENU"] == "MINUTE") monitor.display_name = "minute";
            if (monitor.params["CURRENTMENU"] == "DATE") monitor.display_name = "date";
        } else {
            monitor.value = "unknown opcode";
            monitor.display_name = monitor.opcode;
        }
    }

    // check if all chains have completely stopped running
    if (processed_chains == 0) {
        std::cout << "project is finished running" << std::endl;
        finished = true;
    }
}

Value EngineFunctions::Engine::compute_input(LinkInput input, ScratchTarget* sprite) {
    if (input.reporter_id.has_value())
        return compute_reporter(get_reporter_by_id(input.reporter_id.value()), sprite);

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
    case OPCODE::SET_X_TO: s->set_x(compute_input(link.inputs["X"], s)); break;
    case OPCODE::SET_Y_TO: s->set_y(compute_input(link.inputs["Y"], s)); break;
    case OPCODE::CHANGE_X_BY:
        s->set_x(s->get_x() + compute_input(link.inputs["DX"], s).get_number());
        break;
    case OPCODE::CHANGE_Y_BY:
        s->set_y(s->get_y() + compute_input(link.inputs["DY"], s).get_number());
        break;
    case OPCODE::POINT_IN_DIRECTION:
        s->set_direction(compute_input(link.inputs["DIRECTION"], s));
        break;
    case OPCODE::GO_TO_XY:
        s->set_x(compute_input(link.inputs["X"], s));
        s->set_y(compute_input(link.inputs["Y"], s));
        break;
    case OPCODE::TURN_LEFT:
        s->set_direction(s->get_direction() -
                         compute_input(link.inputs["DEGREES"], s).get_number());
        break;
    case OPCODE::TURN_RIGHT:
        s->set_direction(s->get_direction() +
                         compute_input(link.inputs["DEGREES"], s).get_number());
        break;
    case OPCODE::MOVE_STEPS: move_steps(compute_input(link.inputs["STEPS"], s), s); break;
    case OPCODE::SET_ROTATION_STYLE: set_rotation_style(link.fields["STYLE"][0], s); break;

    // Control
    case OPCODE::WAIT: wait(compute_input(link.inputs["DURATION"], s).get_number(), c, i); break;
    case OPCODE::FOREVER: forever_loop(link, c, s, i); break;
    case OPCODE::STOP: stop_menu(link, c, s, i); break;
    case OPCODE::IF: if_statement(link, s); break;
    case OPCODE::IF_ELSE: if_else_statement(link, s); break;
    case OPCODE::REPEAT: repeat_loop(link, c, s, i); break;
    case OPCODE::CREATE_CLONE_OF: create_clone_of(link, s); break;
    case OPCODE::START_AS_CLONE:
        if (processing_clones) {
            c.activatable = false;
        } else {
            i = -1;
        }
        break;
    case OPCODE::DELETE_THIS_CLONE:
        if (processing_clones) s->name() = "";
        break;

    // Looks
    case OPCODE::SAY_FOR_SECS: say_for_sec(link, s, c, i); break;
    case OPCODE::SAY: say(link, s); break;
    case OPCODE::SHOW: s->set_visible(true); break;
    case OPCODE::HIDE: s->set_visible(false); break;
    case OPCODE::SWITCH_TO_COSTUME: switch_costume_to(link, s); break;
    case OPCODE::NEXT_COSTUME: next_costume(s); break;
    case OPCODE::SET_EFFECT_TO: set_effect_to(link, s); break;
    case OPCODE::CHANGE_EFFECT_BY: change_effect_by(link, s); break;
    case OPCODE::CLEAR_GRAPHIC_EFFECTS:
        s->effects() = {{"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
                        {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
        break;
    case OPCODE::GO_TO_LAYER: go_to_layer(link.fields["FRONT_BACK"][0], s); break;
    case OPCODE::CHANGE_LAYER_BY: change_layer_by(link, s); break;
    case OPCODE::SET_SIZE_TO: s->set_size(compute_input(link.inputs["SIZE"], s)); break;
    case OPCODE::CHANGE_SIZE_BY:
        s->set_size(s->get_size() + compute_input(link.inputs["CHANGE"], s).get_number());
        break;

    // Sensing
    case OPCODE::RESET_TIMER: timer = std::chrono::high_resolution_clock::now(); break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'"
                  << std::endl;
        break;
    }
}