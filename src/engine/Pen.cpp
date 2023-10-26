#include "Pen.hpp"

void EngineFunctions::Pen::update(double x, double y) {
    if (!last_x.has_value() && !last_y.has_value()) {
        last_x = x;
        last_y = y;
        return;
    }
    if (last_x.value() == x && last_y.value() == y) return;

    if (pen_active) draw_line(last_x.value(), last_y.value(), x, y);

    last_x = x;
    last_y = y;
}

void EngineFunctions::Pen::draw_line(double x1, double y1, double x2, double y2) {
    pen_orders.push_back(PenDrawOrder(x1, y1, x2, y2, settings));
}

EngineFunctions::RGB EngineFunctions::Pen::scratch_color_to_rgb(double color) {
    RGB out = RGB();

    double H = std::clamp(color, 0.0, 100.0) * 360 / 100;
    double S = settings.pen_saturation;
    double V = settings.pen_brightness;

    // std::cout << "getting rgb of hsv: " << H << " " << S << " " << V << std::endl;

    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    } else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    } else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    } else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    } else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }

    out.r = (r + m) * 255;
    out.g = (g + m) * 255;
    out.b = (b + m) * 255;

    // std::cout << "output rgb: " << out.r << " " << out.g << " " << out.b << std::endl;

    return out;
}