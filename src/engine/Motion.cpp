#include "Engine.hpp"

void EngineFunctions::move_steps(Link link, ScratchSprite& s, Engine& e) {
    float dir = (s.direction - 90) * (3.1415926 / 180);
    float steps = std::get<int>(e.parse_array_block(link.inputs["STEPS"][1]));
    s.x = s.x + (steps * cos(dir));
    s.y = s.y + (steps * sin(dir));
}