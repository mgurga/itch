#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchList {
public:
    ScratchList(json sv, std::string id):
        name(sv[0].get<std::string>()),
        id(id)
    {
        for (auto v : sv[1]) {
            values.push_back(v);
        }
    };

    std::string name;
    std::vector<std::string> values;
    std::string id;
};