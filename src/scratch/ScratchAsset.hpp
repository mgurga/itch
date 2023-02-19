#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchAsset {
public:
    ScratchAsset(json sa);

    std::string name;
    std::string dataFormat;
    std::string assetId;
    std::string md5ext;
};