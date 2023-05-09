#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "ScratchTarget.hpp"

class ScratchStage : public ScratchTarget {
public:
    ScratchStage();
    ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload = true);

    int& tempo() { return m_tempo; }
    VideoState& videoState() { return m_videoState; }
    int& videoTransparency() { return m_videoTransparency; }
    std::string& textToSpeechLanguage() { return m_textToSpeechLanguage; }

private:
    int m_tempo;
    VideoState m_videoState;
    int m_videoTransparency;
    std::string m_textToSpeechLanguage;
};