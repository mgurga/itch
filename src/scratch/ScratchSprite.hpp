#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "ScratchStage.hpp"
#include "ScratchTarget.hpp"

class ScratchSprite : public ScratchTarget {
public:
    ScratchSprite(json ss, std::filesystem::path temp_dir, bool heavyload = true);

    bool& visible() { return m_visible; }
    double& x() { return m_x; }
    double& y() { return m_y; }
    double& size() { return m_size; }
    double& direction() { return m_direction; }
    bool& draggable() { return m_draggable; }
    RotationStyle& rotationStyle() { return m_rotationStyle; }

private:
    bool m_visible;
    double m_x, m_y, m_size, m_direction;
    bool m_draggable;
    RotationStyle m_rotationStyle;
};