#include "Engine.hpp"

EngineFunctions::Engine::Engine(Project& project):
    TOTAL_CHAINS(count_chains(project))
{
    prj = &project;
    for (ScratchVariable sv : project.stage.variables) {
        variables.push_back(Variable(sv));
    }

    for (ScratchSprite sprite : project.sprites) {
        for (ScratchVariable sv : sprite.variables) {
            Variable newvar = Variable(sv);
            newvar.make_local(sprite.name);
            variables.push_back(newvar);
        }
    }

    std::cout << "initialized " << variables.size() << " variable(s)" << std::endl;
    for (Variable v : variables) {
        std::cout << "'" << v.name << "', ";
    }
    std::cout << std::endl;

    for (ScratchBlock& b : project.stage.blocks) {
        OPCODE bop = Opcodes::opcode_to_enum(b.opcode);
        if (bop >= 400 && bop < 500)
            operators.push_back(b);
    }

    for (ScratchSprite& sprite : project.sprites) {
        for (ScratchBlock& b : sprite.blocks) {
            OPCODE bop = Opcodes::opcode_to_enum(b.opcode);
            if (bop >= 400 && bop < 500)
                operators.push_back(b);
        }
    }

    std::cout << "found " << operators.size() << " operator(s)" << std::endl;
}

void EngineFunctions::Engine::tick(PlayerInfo* player_info) {
    if (finished) return;
    broadcasts = queued_broadcasts;
    queued_broadcasts.clear();

    pi = player_info;

    // delete old messages
    auto cur = std::chrono::high_resolution_clock::now();
    say_logs.erase(std::remove_if(say_logs.begin(), say_logs.end(), [&cur](SpriteMessage sm) {
        return (sm.end_time <= cur);
    }), say_logs.end());

    int processed_chains = 0;
    // hack to treat ScratchStage as a ScratchSprite
    for (Chain& chain : prj->stage.chains) {
        if (process_chain(chain, dynamic_cast<ScratchSprite*>(&prj->stage))) {
            processed_chains++;
        }
    }

    for (ScratchSprite& sprite : prj->sprites) {
        for (Chain& chain : sprite.chains) {
            if(process_chain(chain, &sprite)) {
                processed_chains++;
            }
        }
    }

    broadcasts.clear();

    if (processed_chains == 0) {
        std::cout << "project is finished running" << std::endl;
        finished = true;
    }
}

std::variant<std::string, double> EngineFunctions::Engine::compute_operator(std::string opid) {
    Link op = get_operator_by_id(opid);

    // basic math operations: add, subtract, multiple, divide
    if (op.opcode >= 400 && op.opcode <= 403) {
        std::variant<std::string, double> num1, num2;
        num1 = compute_input(op.inputs["NUM1"]);
        num2 = compute_input(op.inputs["NUM2"]);

        if (std::holds_alternative<double>(num1) && std::holds_alternative<double>(num2)) {
            switch(op.opcode) {
            case OPERATOR_ADD:
                return std::get<double>(num1) + std::get<double>(num2);
            case OPERATOR_SUBTRACT:
                return std::get<double>(num1) - std::get<double>(num2);
            case OPERATOR_MULTIPLY:
                return std::get<double>(num1) * std::get<double>(num2);
            case OPERATOR_DIVIDE:
                return std::get<double>(num1) / std::get<double>(num2);
            default:
                return 1234.5678;
            }
        } else if (std::holds_alternative<double>(num1)) {
            return std::get<double>(num1);
        } else if (std::holds_alternative<double>(num2)) {
            return std::get<double>(num2);
        } else {
            return {};
        }
    }

    switch (op.opcode) {
    case OPERATOR_JOIN:
        return variant_str(compute_input(op.inputs["STRING1"])) + variant_str(compute_input(op.inputs["STRING2"]));
    default:
        return "unknown operator";
    }

    return {};
}

std::variant<std::string, double> EngineFunctions::Engine::compute_input(json input) {
    if (input[0] == 3 && input[1].is_string())
        return compute_operator(input[1]);

    ScratchArrayBlock sab = ScratchArrayBlock(input[1]);
    switch (sab.type) {
    case Number: case Positive_Integer: case Positive_Number: case Integer: case Angle:
        return sab.num_val;
    case Color: case String: case Broadcast:
        return sab.str_value;
    case VariableType: case ListType:
        return get_var_by_name(sab.str_value).val();
    default:
        return {};
    }
}

bool EngineFunctions::Engine::process_chain(Chain& chain, ScratchSprite* s) {
    if (chain.activatable || !chain.continue_at.empty()) {
        // used to interrupt continue_at if WHEN_KEY_CLICKED, BROADCAST_RECIEVED, or other special events activate
        if (chain.links.at(0).opcode >= WHEN_FLAG_CLICKED && chain.links.at(0).opcode <= BROADCAST_AND_WAIT) {
            int init_link = 0;
            process_link(chain.links.at(0), chain, s, init_link);
        }

        // resume i to continue_at if set
        int start_link = 0;
        if (!chain.continue_at.empty())
            start_link = chain.continue_at.back().link_num;

        // process all other links in chain
        for (int i = start_link; i < chain.links.size(); i++) {
            process_link(chain.links.at(i), chain, s, i);
            if (i == -1) break;
        }
        return true;
    }
    return false;
}

void EngineFunctions::Engine::process_link(Link& link, Chain& c, ScratchSprite* s, int& i) {
    // std::cout << "processing link opcode: " << link.string_opcode << std::endl;
    if (s == nullptr) {
        // throw std::invalid_argument("scratch sprite pointer is null when processing link");
        std::cout << "scratch sprite pointer is null when processing link with opcode " << link.string_opcode << std::endl;
        return;
    }

    switch (link.opcode) {
    // Variables
    case OPCODE::SET_VARIABLE_TO:
        get_var_by_name(link.fields["VARIABLE"][0].get<std::string>()) = compute_input(link.inputs["VALUE"]);
        break;
    case OPCODE::CHANGE_VARIABLE_BY:
        get_var_by_name(link.fields["VARIABLE"][0].get<std::string>()) += std::get<double>(compute_input(link.inputs["VALUE"]));
        break;

    // Events
    case OPCODE::WHEN_FLAG_CLICKED: c.activatable = false; break;
    case OPCODE::WHEN_KEY_PRESSED:
        if (!(std::find(pi->pressed.begin(), pi->pressed.end(), link.fields["KEY_OPTION"][0]) != pi->pressed.end())) {
            i = -1;
        } else {
            c.continue_at.clear();
        }
        break;
    case OPCODE::WHEN_BROADCAST_RECEIVED:
        if (!(std::find(broadcasts.begin(), broadcasts.end(), link.fields["BROADCAST_OPTION"][0]) != broadcasts.end())) {
            i = -1;
        } else {
            c.continue_at.clear();
        }
        break;
    case OPCODE::BROADCAST:
        queued_broadcasts.push_back(std::get<std::string>(compute_input(link.inputs["BROADCAST_INPUT"])));
        break;

    // Motion
    case OPCODE::GO_TO: go_to_menu(link, s); break;
    case OPCODE::SET_X_TO: s->x = std::get<double>(compute_input(link.inputs["X"])); break;
    case OPCODE::SET_Y_TO: s->y = std::get<double>(compute_input(link.inputs["Y"])); break;
    case OPCODE::CHANGE_Y_BY: s->y += std::get<double>(compute_input(link.inputs["DY"])); break;
    case OPCODE::CHANGE_X_BY: s->x += std::get<double>(compute_input(link.inputs["DX"])); break;
    case OPCODE::GO_TO_XY:
        s->x = std::get<double>(compute_input(link.inputs["X"]));
        s->y = std::get<double>(compute_input(link.inputs["Y"]));
        break;
    case OPCODE::POINT_IN_DIRECTION:
        s->direction = std::get<double>(compute_input(link.inputs["DIRECTION"]));
        break;
    case OPCODE::TURN_LEFT:
        s->direction -= std::get<double>(compute_input(link.inputs["DEGREES"]));
        break;
    case OPCODE::TURN_RIGHT:
        s->direction += std::get<double>(compute_input(link.inputs["DEGREES"]));
        break;
    case OPCODE::MOVE_STEPS: move_steps(link, s); break;

    // Control
    case OPCODE::WAIT: wait(std::get<double>(compute_input(link.inputs["DURATION"])), c, i); break;
    case OPCODE::FOREVER: forever_loop(link, c, s, i); break;
    case OPCODE::STOP: stop_menu(link, c, s, i); break;

    // Looks
    case OPCODE::SAY_FOR_SECS: say_for_sec(link, s, c, i); break;
    case OPCODE::SAY: say(link, s); break;
    case OPCODE::SHOW: s->visible = true; break;
    case OPCODE::HIDE: s->visible = false; break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'" << std::endl;
        break;
    }
}