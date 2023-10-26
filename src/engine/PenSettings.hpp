#pragma once

namespace EngineFunctions {

struct RGB {
    int r = 0;
    int g = 0;
    int b = 0;
};

struct PenSettings {
    double pen_size = 1;
    double pen_color = 66.66;
    double pen_saturation = 100;
    double pen_brightness = 100;
    double pen_transparency = 0;
    RGB pen_rgb = {0, 0, 255};
};

}  // namespace EngineFunctions