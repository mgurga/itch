#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "DrawOrder.hpp"
#include "MonitorDrawOrder.hpp"
#include "PenDrawOrder.hpp"
#include "PlayerInfo.hpp"
#include "SpriteDrawOrder.hpp"
#include "StageDrawOrder.hpp"
#include "StampDrawOrder.hpp"

class Player {
public:
    Player(bool& running);
    ~Player() { delete window; }
    void draw();
    void paint(std::vector<std::unique_ptr<DrawOrder>>& draw_orders);
    PlayerInfo get_player_info() {
        return {pressed,     keys_down,   clicked_sprites, hovered_sprites,
                mouse_pos.x, mouse_pos.y, mouse_down,      mouse_pressed};
    }

    bool& running;

private:
    void paint_sprite(sf::RenderTarget& rt, ScratchSprite& sprite);
    void paint_stage(sf::RenderTarget& rt, ScratchStage& stage);
    void paint_monitor(ScratchMonitor& monitor);
    void paint_default_monitor(ScratchMonitor& monitor);
    void paint_large_monitor(ScratchMonitor& monitor);
    void paint_slider_monitor(ScratchMonitor& monitor);
    void paint_list_monitor(ScratchMonitor& monitor);
    void paint_pen_line(PenDrawOrder& dw);
    void paint_pen_point(double x, double y, EngineFunctions::PenSettings& s);
    void paint_pen_stamp(StampDrawOrder& dw);

    unsigned int ww, wh;

    sf::Font font;
    const unsigned MONITOR_FONT_SIZE = 11;
    std::vector<std::string> pressed;
    std::vector<std::string> keys_down;
    std::vector<std::string> clicked_sprites;
    std::vector<std::string> hovered_sprites;
    sf::Vector2i mouse_pos;
    bool mouse_down = false;
    bool mouse_pressed = false;
    sf::RenderWindow* window;
    sf::Image pen_layer;
};