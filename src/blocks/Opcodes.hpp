#pragma once

#include <string>
#include <iostream>

enum OPCODE {
    VARIABLE = -2,
    UNKNOWN = -1,

    // Event Blocks
    WHEN_FLAG_CLICKED = 0, // "event_whenflagclicked"
    WHEN_KEY_PRESSED = 1, // "event_whenkeypressed"
    WHEN_THIS_SPRITE_CLICKED = 2, // "event_whenthisspriteclicked"
    WHEN_GREATER_THAN = 3, // "event_whengreaterthan"
    WHEN_BROADCAST_RECEIVED = 4, // "event_whenbroadcastreceived"
    BROADCAST = 5, // "event_broadcast"
    BROADCAST_AND_WAIT = 6, // "event_broadcastandwait"

    // Motion Blocks
    MOVE_STEPS = 100, // "motion_movesteps"
    TURN_RIGHT = 101, // "motion_turnright"
    TURN_LEFT = 102, // "motion_turnleft"
    GO_TO = 103, // "motion_goto"
    GO_TO_XY = 104, // "motion_gotoxy"
    GLIDE_TO = 105, // "motion_glideto"
    GLIDE_TO_XY = 106, // "motion_glidesecstoxy"
    POINT_IN_DIRECTION = 107, // "motion_pointindirection"
    POINT_TOWARDS = 108, // "motion_pointtowards"
    CHANGE_X_BY = 109, // "motion_changexby"
    SET_X_TO = 110, // "motion_setx"
    CHANGE_Y_BY = 111, // "motion_changeyby"
    SET_Y_TO = 112, // "motion_sety"
    IF_ON_EDGE_BOUNCE = 113, // "motion_ifonedgebounce"
    SET_ROTATION_STYLE = 114, // "motion_setrotationstyle"
    X_POS = 115, // "motion_xposition"
    Y_POS = 116, // "motion_yposition"
    DIRECTION = 117, // "motion_direction"

    // Looks Blocks
    SAY_FOR_SECS = 200, // "looks_sayforsecs"
    SAY = 201, // "looks_say"
    THINK_FOR_SECS = 202, // "looks_thinkforsecs"
    THINK = 203, // "looks_think"
    SWITCH_TO_COSTUME = 204, // "looks_switchcostumeto"
    NEXT_COSTUME = 205, // "looks_nextcostume"
    SWITCH_TO_BACKDROP = 206, // "looks_switchbackdropto"
    NEXT_BACKDROP = 207, // "looks_nextbackdrop"
    CHANGE_SIZE_BY = 208, // "looks_changesizeby"
    SET_SIZE_TO = 209, // "looks_setsizeto"
    CHANGE_EFFECT_BY = 210, // "looks_changeeffectby"
    SET_EFFECT_TO = 211, // "looks_seteffectto"
    CLEAR_GRAPHIC_EFFECTS = 212, // "looks_cleargraphiceffects"
    SHOW = 213, // "looks_show"
    HIDE = 214, // "looks_hide"
    GO_TO_LAYER = 215, // "looks_gotofrontback"
    CHANGE_LAYER_BY = 216, // "looks_goforwardbackwardlayers"
    COSTUME_NUM_NAME = 217, // "looks_costumenumbername"
    BACKDROP_NUM_NAME = 218, // "looks_backdropnumbername"
    SIZE = 219 // "looks_size"
};

class Opcodes {
public:
    static OPCODE opcode_to_enum(std::string opcode) {
        // events
        if (opcode == "event_whenflagclicked")
            return OPCODE::WHEN_FLAG_CLICKED;
        if (opcode == "event_whenkeypressed")
            return OPCODE::WHEN_KEY_PRESSED;
        if (opcode == "event_whenthisspriteclicked")
            return OPCODE::WHEN_THIS_SPRITE_CLICKED;
        if (opcode == "event_whengreaterthan")
            return OPCODE::WHEN_GREATER_THAN;
        if (opcode == "event_whenbroadcastreceived")
            return OPCODE::WHEN_BROADCAST_RECEIVED;
        if (opcode == "event_broadcast")
            return OPCODE::BROADCAST;
        if (opcode == "event_broadcastandwait")
            return OPCODE::BROADCAST_AND_WAIT;

        // motion
        if (opcode == "motion_movesteps")
            return OPCODE::MOVE_STEPS;
        if (opcode == "motion_turnright")
            return OPCODE::TURN_RIGHT;
        if (opcode == "motion_turnleft")
            return OPCODE::TURN_LEFT;
        if (opcode == "motion_goto")
            return OPCODE::GO_TO;
        if (opcode == "motion_gotoxy")
            return OPCODE::GO_TO_XY;
        if (opcode == "motion_glideto")
            return OPCODE::GLIDE_TO;
        if (opcode == "motion_glidesecstoxy")
            return OPCODE::GLIDE_TO_XY;
        if (opcode == "motion_pointindirection")
            return OPCODE::POINT_IN_DIRECTION;
        if (opcode == "motion_pointtowards")
            return OPCODE::POINT_TOWARDS;
        if (opcode == "motion_changexby")
            return OPCODE::CHANGE_X_BY;
        if (opcode == "motion_setx")
            return OPCODE::SET_X_TO;
        if (opcode == "motion_changeyby")
            return OPCODE::CHANGE_Y_BY;
        if (opcode == "motion_sety")
            return OPCODE::SET_Y_TO;
        if (opcode == "motion_ifonedgebounce")
            return OPCODE::IF_ON_EDGE_BOUNCE;
        if (opcode == "motion_setrotationstyle")
            return OPCODE::SET_ROTATION_STYLE;
        if (opcode == "motion_xposition")
            return OPCODE::X_POS;
        if (opcode == "motion_yposition")
            return OPCODE::Y_POS;
        if (opcode == "motion_direction")
            return OPCODE::DIRECTION;

        // looks
        if (opcode == "looks_sayforsecs")
            return OPCODE::SAY_FOR_SECS;
        if (opcode == "looks_say")
            return OPCODE::SAY;
        if (opcode == "looks_thinkforsecs")
            return OPCODE::THINK_FOR_SECS;
        if (opcode == "looks_think")
            return OPCODE::THINK;
        if (opcode == "looks_switchcostumeto")
            return OPCODE::SWITCH_TO_COSTUME;
        if (opcode == "looks_nextcostume")
            return OPCODE::NEXT_COSTUME;
        if (opcode == "looks_switchbackdropto")
            return OPCODE::SWITCH_TO_BACKDROP;
        if (opcode == "looks_nextbackdrop")
            return OPCODE::NEXT_BACKDROP;
        if (opcode == "looks_changesizeby")
            return OPCODE::CHANGE_SIZE_BY;
        if (opcode == "looks_setsizeto")
            return OPCODE::SET_SIZE_TO;
        if (opcode == "looks_changeeffectby")
            return OPCODE::CHANGE_EFFECT_BY;
        if (opcode == "looks_seteffectto")
            return OPCODE::SET_EFFECT_TO;
        if (opcode == "looks_cleargraphiceffects")
            return OPCODE::CLEAR_GRAPHIC_EFFECTS;
        if (opcode == "looks_show")
            return OPCODE::SHOW;
        if (opcode == "looks_hide")
            return OPCODE::HIDE;
        if (opcode == "looks_gotofrontback")
            return OPCODE::GO_TO_LAYER;
        if (opcode == "looks_goforwardbackwardlayers")
            return OPCODE::CHANGE_LAYER_BY;
        if (opcode == "looks_costumenumbername")
            return OPCODE::COSTUME_NUM_NAME;
        if (opcode == "looks_backdropnumbername")
            return OPCODE::BACKDROP_NUM_NAME;
        if (opcode == "looks_size")
            return OPCODE::SIZE;

        // special
        if (opcode == "variable")
            return OPCODE::VARIABLE;

        std::cout << "unknown opcode detected: '" << opcode << "'" << std::endl;
        return OPCODE::UNKNOWN;
    }
};