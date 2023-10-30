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

    double h = std::clamp(color * 360 / 100, 0.0, 359.0);
    double s = settings.pen_saturation / 100;
    double v = settings.pen_brightness / 100;

    const float hex = h / 60.0;
    const unsigned char primary = (int)hex;
    const float secondary = hex - primary;

    const float x = (1.0 - s) * v;
    const float y = (1.0 - (s * secondary)) * v;
    const float z = (1.0 - (s * (1.0 - secondary))) * v;

    auto mult = [](float i) -> float { return (i * 255.0) + 0.5; };

    switch (primary) {
    case 0:
        out.r = mult(v);
        out.g = mult(z);
        out.b = mult(x);
        break;
    case 1:
        out.r = mult(y);
        out.g = mult(v);
        out.b = mult(x);
        break;
    case 2:
        out.r = mult(x);
        out.g = mult(v);
        out.b = mult(z);
        break;
    case 3:
        out.r = mult(x);
        out.g = mult(y);
        out.b = mult(v);
        break;
    case 4:
        out.r = mult(z);
        out.g = mult(x);
        out.b = mult(v);
        break;
    case 5:
        out.r = mult(v);
        out.g = mult(x);
        out.b = mult(y);
        break;
    }

    return out;
}