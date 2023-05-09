#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../blocks/Chain.hpp"
#include "../blocks/Link.hpp"
#include "ScratchBlock.hpp"
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

    // target variables
    std::string& name() { return m_name; }
    bool isStage() { return m_isStage; }
    unsigned int& volume() { return m_volume; }
    int& layerOrder() { return m_layerOrder; }
    unsigned int& currentCostume() { return m_currentCostume; }
    std::unordered_map<std::string, double>& effects() { return m_effects; }

    // sprite variables
    virtual bool& visible() {
        bool v = true;
        return v;
    }
    virtual double& x() {
        double x = 0.0;
        return x;
    }
    virtual double& y() {
        double y = 0.0;
        return y;
    }
    virtual double& size() {
        double s = 100;
        return s;
    }
    virtual double& direction() {
        double d = 90;
        return d;
    }
    virtual bool& draggable() {
        bool d = false;
        return d;
    }
    virtual RotationStyle& rotationStyle() {
        RotationStyle r = RotationStyle::DONT_ROTATE;
        return r;
    }

    // stage variables
    virtual int& tempo() {
        int t = 100;
        return t;
    }
    virtual VideoState& videoState() {
        VideoState v = VideoState::ON;
        return v;
    }
    virtual int& videoTransparency() {
        int v = 0;
        return v;
    }
    virtual std::string& textToSpeechLanguage() {
        std::string s = "";
        return s;
    }

private:
    bool m_isStage;
    std::string m_name;
    unsigned int m_volume;
    int m_layerOrder;
    unsigned int m_currentCostume;
    std::unordered_map<std::string, double> m_effects = {
        {"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
        {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
};
