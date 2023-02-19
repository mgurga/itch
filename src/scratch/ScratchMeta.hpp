#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchMeta
{
public:
    ScratchMeta();
    ScratchMeta(json sm);

    std::string semver;
    std::string vm;
    std::string agent;
};