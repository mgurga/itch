#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(Link link, ScratchSprite* s) {
    float dir = (s->direction - 90) * (3.1415926 / 180);
    float steps = std::get<int>(compute_input(link.inputs["STEPS"][1]));
    s->x = s->x + (steps * cos(dir));
    s->y = s->y + (steps * sin(dir));
}