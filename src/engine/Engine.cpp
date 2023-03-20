#include "Engine.hpp"

EngineFunctions::Engine::Engine(Project& project) {
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

void EngineFunctions::Engine::tick(Project& project, PlayerInfo* player_info) {
    broadcasts = queued_broadcasts;
    queued_broadcasts.clear();

    prj = &project;
    pi = player_info;

    // hack to treat ScratchStage as a ScratchSprite
    for (Chain& chain : project.stage.chains) {
        if (chain.activatable)
            for (int i = 0; i < chain.links.size(); i++) {
                process_link(chain.links.at(i), chain, dynamic_cast<ScratchSprite*>(&project.stage), i, player_info->pressed);
                if (i == -1) break;
            }
    }

    for (ScratchSprite& sprite : project.sprites) {
        for (Chain& chain : sprite.chains) {
            if (chain.activatable)
                for (int i = 0; i < chain.links.size(); i++) {
                    process_link(chain.links.at(i), chain, &sprite, i, player_info->pressed);
                    if (i == -1) break;
                }
        }
    }

    broadcasts.clear();
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
    for (Link& op : operators) {
        if (op.block_id == id)
            return op;
    }
    throw std::invalid_argument("operator with id '" + id + "' not found");
}

std::string EngineFunctions::Engine::variant_str(std::variant<std::string, double> varient) {
    if (std::holds_alternative<double>(varient))
        return std::to_string(std::get<double>(varient));
    return std::get<std::string>(varient);
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
        std::string str1 = variant_str(compute_input(op.inputs["STRING1"]));
        std::string str2 = variant_str(compute_input(op.inputs["STRING2"]));
        return str1 + str2;
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

void EngineFunctions::Engine::process_link(Link& link, Chain& c, ScratchSprite* s, int& i, std::vector<std::string>& pressed) {
    // std::cout << "processing link opcode: " << link.string_opcode << std::endl;

    switch (link.opcode) {
    // Variables
    case OPCODE::SET_VARIABLE_TO:
        get_var_by_name(link.fields["VARIABLE"][0].get<std::string>()) = compute_input(link.inputs["VALUE"]);
        break;
    case OPCODE::CHANGE_VARIABLE_BY:
        get_var_by_name(link.fields["VARIABLE"][0].get<std::string>()) += std::get<double>(compute_input(link.inputs["VALUE"]));
        break;

    // Events
    case OPCODE::WHEN_FLAG_CLICKED:
        c.activatable = false;
        break;
    case OPCODE::WHEN_KEY_PRESSED:
        if (!(std::find(pressed.begin(), pressed.end(), link.fields["KEY_OPTION"][0]) != pressed.end())) i = -1;
        break;
    case OPCODE::WHEN_BROADCAST_RECEIVED:
        if (!(std::find(broadcasts.begin(), broadcasts.end(), link.fields["BROADCAST_OPTION"][0]) != broadcasts.end())) i = -1;
        break;
    case OPCODE::BROADCAST:
        queued_broadcasts.push_back(std::get<std::string>(compute_input(link.inputs["BROADCAST_INPUT"])));
        break;

    // Motion
    case OPCODE::GO_TO:
        go_to_menu(link, s);
        break;
    case OPCODE::GO_TO_XY:
        s->x = std::get<double>(compute_input(link.inputs["X"]));
        s->y = std::get<double>(compute_input(link.inputs["Y"]));
        break;
    case OPCODE::SET_X_TO:
        s->x = std::get<double>(compute_input(link.inputs["X"]));
        break;
    case OPCODE::SET_Y_TO:
        s->y = std::get<double>(compute_input(link.inputs["Y"]));
        break;
    case OPCODE::CHANGE_Y_BY:
        s->y += std::get<double>(compute_input(link.inputs["DY"]));
        break;
    case OPCODE::CHANGE_X_BY:
        s->x += std::get<double>(compute_input(link.inputs["DX"]));
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
    case OPCODE::MOVE_STEPS:
        move_steps(link, s);
        break;

    // Looks
    case OPCODE::SAY_FOR_SECS:
        std::cout << s->name << " says \"";
        std::cout << std::get<std::string>(compute_input(link.inputs["MESSAGE"]));
        std::cout << "\" for ";
        std::cout << std::get<double>(compute_input(link.inputs["SECS"]));
        std::cout << " second(s)" << std::endl;
        break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'" << std::endl;
        break;
    }
}