#include "Engine.hpp"

void EngineFunctions::Engine::set_pen_param(Link& link, ScratchTarget* s) {
    Value val = compute_input(link.inputs["VALUE"], s);
    std::string param = get_link_by_id(link.inputs["COLOR_PARAM"][1]).fields["colorParam"][0];

    if (param == "color") {
        // TODO: support string color names e.g. "red", "blue"
        s->pen.set_pen_color(val.get_number());
    } else if (param == "saturation") {
        s->pen.set_pen_saturation(val.get_number());
    } else if (param == "brightness") {
        s->pen.set_pen_brightness(val.get_number());
    } else if (param == "transparency") {
        s->pen.set_pen_transparency(val.get_number());
    } else {
        std::cout << "unknown pen parameter: " << param << std::endl;
    }
}

void EngineFunctions::Engine::change_pen_param(Link& link, ScratchTarget* s) {
    Value val = compute_input(link.inputs["VALUE"], s);
    std::string param = get_link_by_id(link.inputs["COLOR_PARAM"][1]).fields["colorParam"][0];

    if (param == "color") {
        s->pen.set_pen_color(s->pen.get_pen_color() + val.get_number());
    } else if (param == "saturation") {
        s->pen.set_pen_saturation(s->pen.get_pen_saturation() + val.get_number());
    } else if (param == "brightness") {
        s->pen.set_pen_brightness(s->pen.get_pen_brightness() + val.get_number());
    } else if (param == "transparency") {
        s->pen.set_pen_transparency(s->pen.get_pen_transparency() + val.get_number());
    } else {
        std::cout << "unknown pen parameter: " << param << std::endl;
    }
}

void EngineFunctions::Engine::set_pen_color_to_color(Link& link, ScratchTarget* s) {
    std::string hexcolor = compute_input(link.inputs["COLOR"], s);
    unsigned int color;

    std::stringstream ss;
    hexcolor.erase(0, 1);
    ss << std::hex << hexcolor;
    ss >> color;

    RGB c;
    c.r = ((color >> 16) & 0xFF);
    c.g = ((color >> 8) & 0xFF);
    c.b = ((color) & 0xFF);

    s->pen.set_pen_color(c);
}