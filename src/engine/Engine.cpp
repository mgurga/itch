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

    std::cout << "initalized " << variables.size() << " variable(s)" << std::endl;
}

void EngineFunctions::Engine::tick(Project& project, std::vector<std::string>& pressed) {
    // hack to treat ScratchStage as a ScratchSprite
    for (Chain& chain : project.stage.chains) {
        if (chain.activatable)
            for (int i = 0; i < chain.links.size(); i++) {
                process_link(chain.links.at(i), chain, dynamic_cast<ScratchSprite*>(&project.stage), i, pressed);
                if (i == -1) break;
            }
    }

    for (ScratchSprite& sprite : project.sprites) {
        for (Chain& chain : sprite.chains) {
            if (chain.activatable)
                for (int i = 0; i < chain.links.size(); i++) {
                    process_link(chain.links.at(i), chain, &sprite, i, pressed);
                    if (i == -1) break;
                }
        }
    }
}

Variable& EngineFunctions::Engine::get_variable_by_name(std::string name) {
    for (Variable& var : variables)
        if (var.name == name)
            return var;
    throw std::invalid_argument("variable '" + name + "' not found");
}

std::variant<std::string, int> EngineFunctions::Engine::compute_input(json block) {
    ScratchArrayBlock sab = ScratchArrayBlock(block);
    switch (sab.type) {
    case Number: case Positive_Integer: case Positive_Number: case Integer: case Angle:
        return sab.num_val;
    case Color: case String:
        return sab.str_value;
    case VariableType: case ListType:
        return get_variable_by_name(sab.str_value).val();
    default:
        return {};
    }
}

void EngineFunctions::Engine::process_link(Link& link, Chain& c, ScratchSprite* s, int& i, std::vector<std::string>& pressed) {
    switch (link.opcode) {
    // Variables
    case OPCODE::SET_VARIABLE_TO:
        get_variable_by_name(link.fields["VARIABLE"][0]) = compute_input(link.inputs["VALUE"][1]);
        break;
    case OPCODE::CHANGE_VARIABLE_BY:
        get_variable_by_name(link.fields["VARIABLE"][0]) += std::get<int>(compute_input(link.inputs["VALUE"][1]));
        break;

    // Events
    case OPCODE::WHEN_FLAG_CLICKED:
        c.activatable = false;
        break;
    case OPCODE::WHEN_KEY_PRESSED:
        if (!(std::find(pressed.begin(), pressed.end(), link.fields["KEY_OPTION"][0]) != pressed.end())) i = -1;
        break;

    // Motion
    case OPCODE::SET_X_TO:
        s->x = std::get<int>(compute_input(link.inputs["X"][1]));
        break;
    case OPCODE::SET_Y_TO:
        s->y = std::get<int>(compute_input(link.inputs["Y"][1]));
        break;
    case OPCODE::CHANGE_Y_BY:
        s->y += std::get<int>(compute_input(link.inputs["DY"][1]));
        break;
    case OPCODE::CHANGE_X_BY:
        s->x += std::get<int>(compute_input(link.inputs["DX"][1]));
        break;
    case OPCODE::POINT_IN_DIRECTION:
        s->direction = std::get<int>(compute_input(link.inputs["DIRECTION"][1]));
        break;
    case OPCODE::TURN_LEFT:
        s->direction -= std::get<int>(compute_input(link.inputs["DEGREES"][1]));
        break;
    case OPCODE::TURN_RIGHT:
        s->direction += std::get<int>(compute_input(link.inputs["DEGREES"][1]));
        break;
    case OPCODE::MOVE_STEPS:
        move_steps(link, s);
        break;

    // Looks
    case OPCODE::SAY_FOR_SECS:
        std::cout << s->name << " says \"" << " " << "\" for " << std::get<std::string>(compute_input(link.inputs["SECS"][1])) << " seconds" << std::endl;
        break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'" << std::endl;
        break;
    }
}