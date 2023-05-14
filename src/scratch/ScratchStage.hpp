#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "ScratchTarget.hpp"

class ScratchStage : public ScratchTarget {
public:
    ScratchStage();
    ScratchStage(json ss, std::filesystem::path temp_dir, bool heavyload = true);

    int get_tempo() { return m_tempo; }
    void set_tempo(int t) { m_tempo = t; }
    VideoState get_video_state() { return m_videoState; }
    void set_video_state(VideoState s) { m_videoState = s; }
    int get_video_transparency() { return m_videoTransparency; }
    void set_video_transparency(int v) { m_videoTransparency = v; }
    virtual std::string get_tts_language() { return m_textToSpeechLanguage; }
    virtual void set_tts_language(std::string t) { m_textToSpeechLanguage = t; }

private:
    int m_tempo;
    VideoState m_videoState;
    int m_videoTransparency;
    std::string m_textToSpeechLanguage;
};