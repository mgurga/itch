#pragma once

#include <memory>
#include <vector>

#include "../player/ClearDrawOrder.hpp"
#include "../player/DrawOrder.hpp"
#include "../player/MonitorDrawOrder.hpp"
#include "../player/PenDrawOrder.hpp"
#include "../player/SpriteDrawOrder.hpp"
#include "../player/StageDrawOrder.hpp"
#include "../player/StampDrawOrder.hpp"

class DrawOrderList {
public:
    DrawOrderList() : draw_order_list() {}

    std::vector<std::unique_ptr<DrawOrder>>& get_draw_order_list() { return draw_order_list; }
    void add_draw_order(std::unique_ptr<DrawOrder> dop) {
        draw_order_list.push_back(std::move(dop));
    }

private:
    std::vector<std::unique_ptr<DrawOrder>> draw_order_list;
};