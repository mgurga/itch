#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <variant>
#include <cmath>
#include "../Project.hpp"
#include "../blocks/Link.hpp"
#include "../blocks/Opcodes.hpp"
#include "Variable.hpp"

namespace EngineFunctions {
class Engine {
public:
    Engine() {};
    Engine(Project& project);

    void tick(Project& project, std::vector<std::string>& pressed);
    void process_link(Link link, ScratchSprite* sprite, int& i, std::vector<std::string>& pressed);
    std::variant<std::string, int> compute_input(json block);
    Variable& get_variable_by_name(std::string name);

    std::vector<Variable> variables;

    void move_steps(Link link, ScratchSprite* s);
};
}