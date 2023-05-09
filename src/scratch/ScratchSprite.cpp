#include "ScratchSprite.hpp"

ScratchSprite::ScratchSprite(json ss, std::filesystem::path temp_dir, bool heavyload) :
    ScratchTarget(ss, temp_dir, heavyload),
    m_x(ss["x"]),
    m_y(ss["y"]),
    m_size(ss["size"]),
    m_direction(ss["direction"]),
    m_draggable(ss["draggable"]),
    m_visible(ss["visible"]) {
    if (ss["rotationStyle"] == "all around") {
        m_rotationStyle = RotationStyle::ALL_AROUND;
    } else if (ss["rotationStyle"] == "left-right") {
        m_rotationStyle = RotationStyle::LEFT_RIGHT;
    } else if (ss["rotationStyle"] == "don't rotate") {
        m_rotationStyle = RotationStyle::DONT_ROTATE;
    } else {
        m_rotationStyle = RotationStyle::ALL_AROUND;
    }
}