#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <variant>

class Value {
public:
    enum SpecialValue { Infinity, NaN, NegativeInfinity, None };

    Value(std::variant<std::string, double> var) {
        if (std::holds_alternative<std::string>(var)) value = std::get<std::string>(var);
        if (std::holds_alternative<double>(var)) value = std::get<double>(var);
    };
    Value(std::variant<std::string, double, bool> var) : value(var){};
    Value(std::string s) {
        if (std::all_of(std::begin(s), std::end(s),
                        [](char c) { return (std::isxdigit(c) || c == '.'); })) {
            try {
                value = std::stod(s);
            } catch (const std::invalid_argument&) { value = s; }
            return;
        }
        value = s;
    };
    Value(double d) : value(d) { update_special_value(); };
    Value(int i) : value(static_cast<double>(i)) { update_special_value(); };
    Value(unsigned int i) : value(static_cast<double>(i)) { update_special_value(); };
    Value(bool b) : value(b){};
    Value(std::size_t s) : value(static_cast<double>(s)) { update_special_value(); };
    Value(char c) : value(std::string(1, c)){};
    Value() : value(""){};

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
            if (is_infinity()) return "Infinity";
            if (is_negative_infinity()) return "-Infinity";
            if (is_nan()) return "NaN";
            s.erase(s.find_last_not_of('0') + 1, std::string::npos);
            s.erase(s.find_last_not_of('.') + 1, std::string::npos);
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
            if (get_bool()) {
                return 1.0;
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

    void update_special_value() {
        if (contains_number()) {
            if (get_number() <= -std::pow(10, 21)) sv = NegativeInfinity;
            if (get_number() >= std::pow(10, 21)) sv = Infinity;
            if (get_number() != get_number()) sv = NaN;
            if (get_number() >= -std::pow(10, -6) && get_number() <= std::pow(10, -6)) value = 0.0;
        }
    }

    bool contains_string() const { return std::holds_alternative<std::string>(value); }
    bool contains_number() const { return std::holds_alternative<double>(value); }
    bool contains_bool() const { return std::holds_alternative<bool>(value); }

    bool is_infinity() const { return sv == Infinity; }
    bool is_negative_infinity() const { return sv == NegativeInfinity; }
    bool is_nan() const { return sv == NaN; }

    Value operator=(Value other) {
        value = other.value;
        sv = other.sv;
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
        if (other.contains_string() || other.contains_bool()) { return *this; }
        if (contains_string() || contains_bool()) {
            value = other.get_number();
            return *this;
        }
        value = get_number() + other.get_number();
        return *this;
    }

    bool operator==(const Value& other) const { return (value == other.value); }

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
    SpecialValue sv = None;
};