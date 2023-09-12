#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using json = nlohmann::json;

class ScratchComment {
public:
    ScratchComment() : x(0), y(0), width(0), height(0), minimized(false), text(""){};
    ScratchComment(json sv) {
        if (!sv["blockId"].is_null()) block_id = sv["blockId"];
        x = sv["x"];
        y = sv["y"];
        width = sv["width"];
        height = sv["height"];
        minimized = sv["minimized"];
        text = sv["text"];
    }

    std::optional<std::string> get_block_id() const { return block_id; }

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_width() const { return width; }
    double get_height() const { return height; }

    bool is_minimized() const { return minimized; }

    std::string get_text() const { return text; }

    friend std::ostream& operator<<(std::ostream& out, const ScratchComment& sc) {
        out << "ScratchComment { text: '" << sc.get_text() << "' "
            << "blockId: " << sc.get_block_id().value_or("none") << " x: " << sc.get_x()
            << " y: " << sc.get_y() << " width: " << sc.get_width()
            << " height: " << sc.get_height() << " minimized: " << sc.is_minimized() << " }";
        return out;
    }

private:
    std::optional<std::string> block_id;
    double x, y, width, height;
    bool minimized;
    std::string text;
};