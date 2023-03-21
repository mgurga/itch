#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchVariable {
public:
    ScratchVariable(json sv, std::string id):
        name(sv[0].get<std::string>()),
        value(to_string(sv[1])),
        isCloud(sv.size() == 3),
        id(id)
    {};

    std::string name;
    std::string value;
    std::string id;
    bool isCloud;
};