#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

class ScratchList {
public:
    ScratchList(json sv, std::string id) : name(sv[0].get<std::string>()), id(id) {
        for (auto v : sv[1]) {
            if (v.type() == nlohmann::detail::value_t::string)
                values.push_back(v.get<std::string>());
            else
                values.push_back(v.dump());
        }
    };

    std::string name;
    std::vector<std::string> values;
    std::string id;
};