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
}

void EngineFunctions::Engine::tick(Project& project, std::vector<std::string>& pressed) {
    // hack to treat ScratchStage as a ScratchSprite
    for (Chain chain : project.stage.chains) {
        for (int i = 0; i < chain.links.size(); i++) {
            process_link(chain.links.at(i), dynamic_cast<ScratchSprite*>(&project.stage), i, pressed);
            if (i == -1) break;
        }
    }

    for (ScratchSprite& sprite : project.sprites) {
        for (Chain chain : sprite.chains) {
            for (int i = 0; i < chain.links.size(); i++) {
                process_link(chain.links.at(i), &sprite, i, pressed);
                if (i == -1) break;
            }
        }
    }
}

Variable& EngineFunctions::Engine::get_variable_by_name(std::string name) {
    for (Variable& var : variables)
        if (var.name == name)
            return var;
    throw std::invalid_argument("sprite '" + name + "' not found");
}

std::variant<std::string, int> EngineFunctions::Engine::parse_array_block(json block) {
    ScratchArrayBlock sab = ScratchArrayBlock(block);
    switch (sab.type) {
    case Number: case Positive_Integer: case Positive_Number: case Integer: case Angle:
        return sab.num_val;
    case Color: case String:
        return sab.str_value;
    case VariableType: case ListType:
        return get_variable_by_name(sab.str_value).value;
    default:
        return {};
    }
}

void EngineFunctions::Engine::process_link(Link link, ScratchSprite* s, int& i, std::vector<std::string>& pressed) {
    switch (link.opcode) {
    // Events
    case WHEN_FLAG_CLICKED:
        break;
    case WHEN_KEY_PRESSED:
        if (!(std::find(pressed.begin(), pressed.end(), link.fields["KEY_OPTION"][0]) != pressed.end())) i = -1;
        break;

    // Motion
    case CHANGE_Y_BY:
        s->y += std::get<int>(parse_array_block(link.inputs["DY"][1]));
        break;
    case POINT_IN_DIRECTION:
        s->direction = std::get<int>(parse_array_block(link.inputs["DIRECTION"][1]));
        break;
    case MOVE_STEPS:
        EngineFunctions::move_steps(link, s, *this);
        break;

    default:
        std::cout << "unknown opcode detected in engine: '" << link.string_opcode << "'" << std::endl;
        break;
    }
}