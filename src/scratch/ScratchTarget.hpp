#pragma once

#include <algorithm>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "../blocks/Chain.hpp"
#include "../blocks/Link.hpp"
#include "ScratchBlock.hpp"
#include "ScratchComment.hpp"
#include "ScratchCostume.hpp"
#include "ScratchList.hpp"
#include "ScratchSound.hpp"
#include "ScratchVariable.hpp"

using json = nlohmann::json;

enum RotationStyle { ALL_AROUND, LEFT_RIGHT, DONT_ROTATE };
enum VideoState { ON, OFF, ON_FLIPPED };

class ScratchTarget {
public:
    ScratchTarget();
    ScratchTarget(json st, std::filesystem::path temp_dir, bool heavyload = true);

    std::vector<ScratchVariable> variables;
    std::vector<ScratchList> lists;
    std::vector<ScratchCostume> costumes;
    std::vector<ScratchSound> sounds;
    std::vector<ScratchBlock> blocks;
    std::vector<Link> links;

    std::vector<Chain> chains;

    ScratchCostume& costume() { return costumes.at(m_currentCostume); }

    // target variables
    std::string get_name() { return m_name; }
    void set_name(std::string s) { m_name = s; }
    bool isStage() { return m_isStage; }
    unsigned int get_volume() { return m_volume; }
    void set_volume(unsigned int v) { m_volume = v; }
    int get_layer_order() { return m_layerOrder; }
    void set_layer_order(int l) { m_layerOrder = l; }
    unsigned int get_current_costume() { return m_currentCostume; }
    void set_current_costume(unsigned int c) { m_currentCostume = c; }

    double get_effect(std::string e) {
        std::transform(e.begin(), e.end(), e.begin(), ::toupper);
        try {
            return m_effects.at(e);
        } catch (std::exception ex) {
            std::cout << "could not find effect: '" << e << "'" << std::endl;
            return 0.0;
        }
    }
    void set_effect(std::string e, double strength) {
        std::transform(e.begin(), e.end(), e.begin(), ::toupper);
        m_effects.at(e) = strength;
    }
    void reset_effects() {
        m_effects = {{"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
                     {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
    }

    // sprite variables
    virtual bool get_visible() { return true; }
    virtual void set_visible(bool b) {}
    virtual double get_x() { return 0.0; }
    virtual void set_x(double d) {}
    virtual double get_y() { return 0.0; }
    virtual void set_y(double d) {}
    virtual int get_size() { return 100; }
    virtual void set_size(int s) {}
    virtual double get_direction() { return 90.0; }
    virtual void set_direction(double d) {}
    virtual bool get_draggable() { return false; }
    virtual void set_draggable(bool b) {}
    virtual RotationStyle get_rotation_style() { return RotationStyle::DONT_ROTATE; }
    virtual void set_rotation_style(RotationStyle r) {}

    // stage variables
    virtual int get_tempo() { return 100; }
    virtual void set_tempo(int t) {}
    virtual VideoState get_video_state() { return VideoState::ON; }
    virtual void set_video_state(VideoState s) {}
    virtual int get_video_transparency() { return 0; }
    virtual void set_video_transparency(int v) {}
    virtual std::string get_tts_language() { return ""; }
    virtual void set_tts_language(std::string t) {}

private:
    bool m_isStage;
    std::string m_name;
    unsigned int m_volume;
    int m_layerOrder;
    unsigned int m_currentCostume;
    std::unordered_map<std::optional<std::string>, ScratchComment> m_comments;
    std::unordered_map<std::string, double> m_effects = {
        {"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
        {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
};
