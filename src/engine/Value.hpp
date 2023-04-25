#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <variant>

class Value {
public:
    Value(std::variant<std::string, double> var) {
        if (std::holds_alternative<std::string>(var))
            value = std::get<std::string>(var);
        if (std::holds_alternative<double>(var))
            value = std::get<double>(var);
    };
    Value(std::variant<std::string, double, bool> var): value(var) {};
    Value(std::string s) {
        if (std::all_of(std::begin(s), std::end(s), [](char c){ return (std::isxdigit(c) || c == '.'); })) {
            try {
                value = std::stod(s);
            } catch (const std::invalid_argument&) {
                value = s;
            }
            return;
        }
        value = s;
    };
    Value(double d): value(d) {};
    Value(int i): value(static_cast<double>(i)) {};
    Value(bool b): value(b) {};
    Value() {};

    operator std::string() { return get_string(); }
    operator double() { return get_number(); }
    operator bool() { return get_bool(); }

    std::variant<std::string, double> get_variant() {
        std::variant<std::string, double> out;

        if (std::holds_alternative<double>(value)) {
            out = std::get<double>(value);
        } else if (std::holds_alternative<std::string>(value)) {
            out = std::get<std::string>(value);
        } else if (std::holds_alternative<bool>(value)) {
            out = std::get<bool>(value) ? "true" : "false";
        } else {
            out = "value empty";
        }

        return out;
    }

    std::string get_string() {
        if (std::holds_alternative<double>(value)) {
            std::string s = std::to_string(std::get<double>(value));
            s.erase (s.find_last_not_of('0') + 1, std::string::npos);
            s.erase (s.find_last_not_of('.') + 1, std::string::npos);
            return s;
        } else if (std::holds_alternative<std::string>(value)) {
            return std::get<std::string>(value);
        } else if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value) ? "true" : "false";
        } else {
            return "value empty";
        }
    }

    double get_number() {
        if (std::holds_alternative<double>(value)) {
            return std::get<double>(value);
        } else if (contains_bool()) {
            // hack to make sure true values are greater than false values
            if (get_bool()) {
                return 1.0; // should be 0.000001 or something but 1 feels more proper
            } else {
                return 0.0;
            }
        } else {
            return 0.0;
        }
    }

    bool get_bool() {
        if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value);
        } else {
            return false;
        }
    }

    bool contains_string() const {
        return std::holds_alternative<std::string>(value);
    }

    bool contains_number() const {
        return std::holds_alternative<double>(value);
    }

    bool contains_bool() const {
        return std::holds_alternative<bool>(value);
    }

    static Value detect_type(std::string s) {
        Value out;
        try {
            out = std::stod(s);
        } catch (const std::invalid_argument&) {
            out = s;
        }
        return out;
    }

    Value operator=(Value other) {
        value = other.value;
        return *this;
    }

    Value operator+=(double& other) {
        if (contains_string() || contains_bool()) {
            value = other;
            return *this;
        }
        value = get_number() + other;
        return *this;
    }

    Value operator+=(Value& other) {
        if (other.contains_string() || other.contains_bool()) {
            return *this;
        }
        if (contains_string() || contains_bool()) {
            value = other.get_number();
            return *this;
        }
        value = get_number() + other.get_number();
        return *this;
    }

    std::string debug_string() {
        std::string out;
        if (contains_string()) {
            out = "[string] ";
        } else if (contains_number()) {
            out = "[double] ";
        } else if (contains_bool()) {
            out = "[bool] ";
        } else {
            out = "[unknown] ";
        }

        return out + get_string();
    }

private:
    std::variant<std::string, double, bool> value;
};