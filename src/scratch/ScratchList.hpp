#pragma once

#include <exception>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

class ScratchList {
public:
    ScratchList(json sv, std::string id) : name(sv[0].get<std::string>()), id(id) {
        for (auto v : sv[1]) {
            try {
                values.push_back(v.get<std::string>());
            } catch (std::exception e) { values.push_back(v.dump()); }
        }
    };

    std::string name;
    std::vector<std::string> values;
    std::string id;
};