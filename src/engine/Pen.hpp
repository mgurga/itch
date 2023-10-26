#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../player/PenDrawOrder.hpp"
#include "PenSettings.hpp"

namespace EngineFunctions {

class Pen {
public:
    Pen() { settings.pen_rgb = scratch_color_to_rgb(settings.pen_color); };

    void pen_down() { pen_active = true; }
    void pen_up() { pen_active = false; }

    void update(double x, double y);

    void set_pen_size(double s) { settings.pen_size = s; }
    double get_pen_size() const { return settings.pen_size; }
    void set_pen_color(double c) {
        settings.pen_rgb = scratch_color_to_rgb(c);
        settings.pen_color = c;
    }
    double get_pen_color() const { return settings.pen_color; }
    void set_pen_saturation(double s) { settings.pen_saturation = s; }
    double get_pen_saturation() const { return settings.pen_saturation; }
    void set_pen_brightness(double b) { settings.pen_brightness = b; }
    double get_pen_brightness() const { return settings.pen_brightness; }
    void set_pen_transparency(double t) { settings.pen_transparency = t; }
    double get_pen_transparency() const { return settings.pen_transparency; }

    std::vector<PenDrawOrder>& get_pen_orders() { return pen_orders; }

private:
    PenSettings settings = {};
    bool pen_active = false;
    std::optional<double> last_x, last_y;
    std::vector<PenDrawOrder> pen_orders;

    void draw_line(double x1, double y1, double x2, double y2);
    RGB scratch_color_to_rgb(double color);
};

}  // namespace EngineFunctions