#pragma once

#include "../engine/PenSettings.hpp"
#include "DrawOrder.hpp"

class PenDrawOrder : public DrawOrder {
public:
    PenDrawOrder(double x, double y, double x2, double y2, EngineFunctions::PenSettings s) :
        DrawOrder(x, y, DrawOrder::PEN_LINE), x2(x2), y2(y2), settings(s) {}

    double get_x2() const { return x2; }
    double get_y2() const { return y2; }
    EngineFunctions::PenSettings get_pen_settings() const { return settings; }

    void set_x2(double x) { x2 = x; }
    void set_y2(double y) { y2 = y; }
    void set_pen_settings(EngineFunctions::PenSettings s) { settings = s; }

private:
    double x2, y2;
    EngineFunctions::PenSettings settings;
};