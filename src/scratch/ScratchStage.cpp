#include "ScratchStage.hpp"

ScratchStage::ScratchStage() {}
ScratchStage::ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload) :
    ScratchTarget(ss, temp_dir, heavyload), m_tempo(ss["tempo"]) {
    if (ss["videoState"] == "on") {
        m_videoState = VideoState::ON;
    } else if (ss["videoState"] == "off") {
        m_videoState = VideoState::OFF;
    } else if (ss["videoState"] == "on-flipped") {
        m_videoState = VideoState::ON_FLIPPED;
    } else {
        m_videoState = VideoState::ON;
    }

    m_textToSpeechLanguage = ss["textToSpeechLanguage"].is_null() ? "" : ss["textToSpeechLanguage"];
}