#include "ScratchStage.hpp"

ScratchStage::ScratchStage() {}
ScratchStage::ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload) :
    ScratchTarget(ss, temp_dir, heavyload), m_tempo(ss["tempo"]) {
    if (ss["videoState"] == "on") {
        m_videoState = ON;
    } else if (ss["videoState"] == "off") {
        m_videoState = OFF;
    } else if (ss["videoState"] == "on-flipped") {
        m_videoState = ON_FLIPPED;
    } else {
        m_videoState = ON;
    }

    m_textToSpeechLanguage = ss["textToSpeechLanguage"].is_null() ? "" : ss["textToSpeechLanguage"];
}