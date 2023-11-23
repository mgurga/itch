#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "ScratchAsset.hpp"
#include "../player/SoundResource.hpp"

using json = nlohmann::json;

class ScratchSound : public ScratchAsset {
public:
    ScratchSound(json ss);
    void load_sound(std::filesystem::path tempdir);

    double rate;
    double sampleCount;

    SoundResource sound;
};