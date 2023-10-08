#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "../scratch/ScratchVariable.hpp"
#include "Value.hpp"

using json = nlohmann::json;

class Variable {
public:
    Variable(std::string name, Value value, std::string id = "") :
        name(name), value(value), id(id), is_global(true), is_cloud(false){};
    Variable(json sv, std::string id = "") :
        name(to_string(sv[0])),
        value(to_string(sv[1])),
        is_cloud(sv.size() == 3),
        is_global(true),
        id(id){};
    Variable(const ScratchVariable& sv) :
        name(sv.name), value(sv.value), is_cloud(sv.isCloud), is_global(true), id(sv.id){};

    std::string name;
    bool is_cloud;
    bool is_global;           // otherwise only available in target
    std::string sprite_name;  // if is_global is false this is sent to the sprite name

    void make_local(std::string sprite_name) {
        is_global = false;
        this->sprite_name = sprite_name;
    }

    std::optional<std::string> get_id() {
        if (id == "") {
            return {};
        } else {
            return id;
        }
    }

    Value val() { return value; }

    Variable operator=(const std::string& other) {
        value = other;
        return *this;
    }

    Variable operator=(const double& other) {
        value = other;
        return *this;
    }

    Variable operator=(Value other) {
        value = other;
        return *this;
    }

    Variable operator+=(double other) {
        value += other;
        return *this;
    }

    Variable operator+=(Value& other) {
        value += other;
        return *this;
    }

private:
    std::string id;
    Value value;
};