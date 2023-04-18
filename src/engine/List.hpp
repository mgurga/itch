#pragma once

#include <string>
#include <vector>

#include "../scratch/ScratchList.hpp"
#include "Value.hpp"

class List {
public:
    List(const ScratchList& sl): name(sl.name), id(sl.id) {
        for (std::string s : sl.values) {
            values.push_back(Value::detect_type(s));
        }
    };

    std::string name;
    bool is_global = true; // otherwise only available in target
    std::string sprite_name; // if is_global is false this is sent to the sprite name
    std::vector<Value> values;
    std::string id;

    void make_local(std::string sprite_name) {
        is_global = false;
        this->sprite_name = sprite_name;
    }
};