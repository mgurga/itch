#pragma once

class DrawOrder {
public:
    enum class DrawObject {
        NONE,
        SPRITE,
        STAGE,
        PEN_LINE,
        SAY_CLOUD,
        THINK_CLOUD,
        MONITOR,
        PEN_CLEAR,
        PEN_STAMP
    };

    DrawOrder(double x, double y, DrawObject t) : x(x), y(y), type(t){};
    virtual ~DrawOrder() {}

    double get_x() const { return x; }
    double get_y() const { return y; }
    DrawObject get_type() const { return type; }

    void set_x(double d) { x = d; }
    void set_y(double d) { y = d; }
    void set_type(DrawObject t) { type = t; }

private:
    double x = 0;
    double y = 0;
    DrawObject type = DrawObject::NONE;
};