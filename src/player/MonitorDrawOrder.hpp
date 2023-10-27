#pragma once

#include "../scratch/ScratchMonitor.hpp"
#include "DrawOrder.hpp"

class MonitorDrawOrder : public DrawOrder {
public:
    MonitorDrawOrder(ScratchMonitor& m) : DrawOrder(m.x, m.y, DrawObject::MONITOR), monitor(m) {}

    ScratchMonitor& get_monitor() const { return monitor; }

private:
    ScratchMonitor& monitor;
};