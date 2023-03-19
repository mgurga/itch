#include "Engine.hpp"

void EngineFunctions::Engine::move_steps(Link link, ScratchSprite* s) {
    double dir = (s->direction - 90) * (3.1415926 / 180);
    double steps = std::get<double>(compute_input(link.inputs["STEPS"]));
    s->x = s->x + (steps * cos(dir));
    s->y = s->y + (steps * sin(dir));
}