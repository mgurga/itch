#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchVariable {
public:
    ScratchVariable(json sv, std::string id):
        name(sv[0].get<std::string>()),
        value(sv[1].get<std::string>()),
        isCloud(sv.size() == 3),
        id(id)
    {};

    std::string name;
    std::string value;
    std::string id;
    bool isCloud;
};