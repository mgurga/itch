#include "ScratchStage.hpp"

ScratchStage::ScratchStage() {}
ScratchStage::ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload):
    ScratchTarget(ss, temp_dir, heavyload),
    tempo(ss["tempo"])
{
    if (ss["videoState"] == "on") {
        videoState = ON;
    } else if (ss["videoState"] == "off") {
        videoState = OFF;
    } else if (ss["videoState"] == "on-flipped") {
        videoState = ON_FLIPPED;
    } else {
        videoState = ON;
    }

    textToSpeechLanguage = ss["textToSpeechLanguage"].is_null() ? "" : ss["textToSpeechLanguage"];
}