#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "ScratchTarget.hpp"

enum VideoState {
    ON,
    OFF,
    ON_FLIPPED
};

class ScratchStage : public ScratchTarget {
public:
    ScratchStage();
    ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload = true);

    virtual ~ScratchStage() = default;

    int tempo;
    VideoState videoState;
    int videoTransparency;
    std::string textToSpeechLanguage;
};