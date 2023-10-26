#pragma once

#include "../scratch/ScratchStage.hpp"
#include "DrawOrder.hpp"

class StageDrawOrder : public DrawOrder {
public:
    StageDrawOrder(ScratchStage& s) : DrawOrder(s.get_x(), s.get_y(), DrawOrder::STAGE), stage(s) {}

    ScratchStage& get_stage() const { return stage; }

private:
    ScratchStage& stage;
};