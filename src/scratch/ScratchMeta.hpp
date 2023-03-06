#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchMeta
{
public:
    ScratchMeta() {};
    ScratchMeta(json sm): semver(sm["semver"]), vm(sm["vm"]), agent(sm["agent"]) {};

    std::string semver;
    std::string vm;
    std::string agent;
};