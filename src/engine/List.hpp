#pragma once

#include <deque>
#include <stdexcept>
#include <string>

#include "../scratch/ScratchList.hpp"
#include "Value.hpp"

class List {
public:
    List(const ScratchList& sl) : name(sl.name), id(sl.id) {
        for (std::string s : sl.values) { values.push_back(Value(s)); }
    };

    std::string name;
    bool is_global = true;    // otherwise only available in target
    std::string sprite_name;  // if is_global is false this is sent to the sprite name
    std::deque<Value> values;
    std::string id;

    void make_local(std::string sprite_name) {
        is_global = false;
        this->sprite_name = sprite_name;
    }

    void delete_all() { values.clear(); }
    void add_to_list(Value v) { values.push_back(v); }
    int length() { return static_cast<int>(values.size()); }

    void set(int pos, Value newVal) {
        if ((pos - 1) < 0) return;
        values.at(pos - 1) = newVal;
    }

    void insert_at(int pos, Value v) {
        if ((pos - 1) < 0) return;
        values.insert(values.begin() + (pos - 1), v);
    }

    Value& at(int pos) {
        if ((pos - 1) < 0)
            throw std::underflow_error(
                "error trying to get list item from a position less than 0, list name: " + name +
                ", position: " + std::to_string(pos - 1));
        return values.at(pos - 1);
    }

    bool contains(Value v) { return std::find(values.begin(), values.end(), v) != values.end(); }

    Value operator[](int pos) {
        if ((pos - 1) < 0) return Value("");
        return values.at(pos - 1);
    }
};