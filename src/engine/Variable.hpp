#pragma once

#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <variant>

#include "../scratch/ScratchVariable.hpp"

using json = nlohmann::json;

class Variable {
public:
    enum VariableType {Integer, String};

    Variable(std::string name, std::string value, std::string id = ""):
        name(name), value(value), id(id), is_global(true), is_cloud(false)
    {};
    Variable(json sv, std::string id = ""):
        name(to_string(sv[0])),
        value(to_string(sv[1])),
        is_cloud(sv.size() == 3),
        is_global(true),
        id(id)
    {};
    Variable(ScratchVariable sv):
        name(sv.name), value(sv.value), is_cloud(sv.isCloud), is_global(true), id(sv.id)
    {};

    std::string name;
    bool is_cloud;
    bool is_global; // otherwise only available in target
    std::string sprite_name; // if is_global is false this is sent to the sprite name
    VariableType type;

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

    std::variant<std::string, int> val() {
        std::variant<std::string, int> out;
        if (type == VariableType::Integer) {
            out = std::stoi(value);
        } else if (type == VariableType::String) {
            out = value;
        }
        return out;
    }

    Variable operator=(const std::string& other) {
        type = VariableType::String;
        value = other;
    }

    Variable operator=(const int& other) {
        type = VariableType::Integer;
        value = other;
    }

    Variable operator=(const std::variant<std::string, int>& other) {
        try {
            value = std::get<std::string>(other);
            type = VariableType::String;
        } catch(const std::bad_variant_access& ex) {
            value = std::get<int>(other);
            type = VariableType::Integer;
        }
    }

    Variable operator+=(const int& other) {
        if (type == VariableType::String) {
            type = VariableType::Integer;
            value = other;
            return;
        } else {
            value = (std::stoi(value) + other);
        }
    }
private:
    std::string id;
    std::string value;
};