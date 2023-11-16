#pragma once

#include <string>

#include "../scratch/ScratchCostume.hpp"
#include "DrawOrder.hpp"

class StampDrawOrder : public DrawOrder {
public:
    StampDrawOrder(double x, double y, ScratchCostume& sc) :
        DrawOrder(x, y, DrawObject::PEN_STAMP), costume(sc) {}

    ScratchCostume& get_costume() const { return costume; }

private:
    double x, y;
    ScratchCostume& costume;
};