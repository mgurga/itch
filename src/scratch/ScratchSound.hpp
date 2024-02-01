#pragma once

#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "../player/SoundResource.hpp"
#include "ScratchAsset.hpp"

using json = nlohmann::json;

class ScratchSound : public ScratchAsset {
public:
    ScratchSound(json ss);
    void load_sound(std::filesystem::path tempdir);

    double rate;
    double sampleCount;

    SoundResource sound;
};