#pragma once

#include "DrawOrder.hpp"

class ClearDrawOrder : public DrawOrder {
public:
    ClearDrawOrder() : DrawOrder(0, 0, DrawObject::PEN_CLEAR) {}
};