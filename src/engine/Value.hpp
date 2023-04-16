#pragma once

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
    Value(std::string s): value(s) {};
    Value(double d): value(d) {};
    Value(int i): value(static_cast<double>(i)) {};
    Value(bool b): value(b) {};

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
            return std::to_string(std::get<double>(value));
        } else if (std::holds_alternative<std::string>(value)) {
            return std::get<std::string>(value);
        } else if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value) ? "true" : "false";
        } else {
            return "value empty";
        }
    }

    double get_double() {
        if (std::holds_alternative<double>(value)) {
            return std::get<double>(value);
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

private:
    std::variant<std::string, double, bool> value;
};