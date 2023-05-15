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

    bool get_visible() { return m_visible; }
    void set_visible(bool b) { m_visible = b; }
    double get_x() { return m_x; }
    void set_x(double d) { m_x = d; }
    double get_y() { return m_y; }
    void set_y(double d) { m_y = d; }
    int get_size() { return m_size; }
    void set_size(int s) { m_size = s; }
    double get_direction() { return m_direction; }
    void set_direction(double d) { m_direction = d; }
    bool get_draggable() { return m_draggable; }
    void set_draggable(bool b) { m_draggable = b; }
    RotationStyle get_rotation_style() { return m_rotationStyle; }
    void set_rotation_style(RotationStyle r) { m_rotationStyle = r; }

private:
    bool m_visible;
    double m_x, m_y, m_size, m_direction;
    bool m_draggable;
    RotationStyle m_rotationStyle;
};