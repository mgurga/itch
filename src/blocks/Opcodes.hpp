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
    SIZE = 219, // "looks_size"

    // Variables
    SET_VARIABLE_TO = 300, // "data_setvariableto"
    CHANGE_VARIABLE_BY = 301, // "data_changevariableby"

    // Operator Symbols
    OPERATOR_ADD = 400, // "operator_add"
    OPERATOR_SUBTRACT = 401, // "operator_subtract"
    OPERATOR_MULTIPLY = 402, // "operator_multiply"
    OPERATOR_DIVIDE = 403, // "operator_divide"
    OPERATOR_RANDOM = 404, // "operator_random"
    OPERATOR_GREATER_THAN = 405, // "operator_gt"
    OPERATOR_LESS_THAN = 406, // "operator_lt"
    OPERATOR_EQUALS = 407, // "operator_equals"
    OPERATOR_AND = 408, // "operator_and"
    OPERATOR_OR = 409, // "operator_or"
    OPERATOR_NOT = 410, // "operator_not"
    OPERATOR_JOIN = 411, // "operator_join"
    OPERATOR_LETTER_OF = 412, // "operator_letter_of"
    OPERATOR_LENGTH = 413, // "operator_length"
    OPERATOR_CONTAINS = 414, // "operator_contains"
    OPERATOR_MOD = 415, // "operator_mod"
    OPERATOR_ROUND = 416, // "operator_round"
    OPERATOR_MATHOP = 417, // "operator_mathop"

    // Control Blocks
    WAIT = 500, // "control_wait"
    REPEAT = 501, // "control_repeat"
    FOREVER = 502, // "control_forever"
    IF = 503, // "control_if"
    IF_ELSE = 504, // "control_if_else"
    WAIT_UNTIL = 505, // "control_wait_until"
    REPEAT_UNTIL = 506, // "control_repeat_until"
    STOP = 507, // "control_stop"
    START_AS_CLONE = 508, // "control_start_as_clone"
    CREATE_CLONE_OF = 509, // "control_create_clone_of"
    DELETE_THIS_CLONE = 510, // "control_delete_this_clone"

    // Sensing Blocks
    TOUCHING_OBJECT = 600, // "sensing_touchingobject"
    TOUCHING_OBJECT_MENU = 601, // "sensing_touchingobjectmenu"
    TOUCHING_COLOR = 602, // "sensing_touchingcolor"
    COLOR_TOUCHING_COLOR = 603, // "sensing_coloristouchingcolor"
    DISTANCE_TO = 604, // "sensing_distanceto"
    DISTANCE_TO_MENU = 605, // "sensing_distancetomenu"
    ASK_AND_WAIT = 606, // "sensing_askandwait"
    ANSWER = 607, // "sensing_answer"
    KEY_PRESSED = 608, // "sensing_keypressed"
    KEY_OPTIONS = 609, // "sensing_keyoptions"
    MOUSE_DOWN = 610, // "sensing_mousedown"
    MOUSE_X = 611, // "sensing_mousex"
    MOUSE_Y = 612, // "sensing_mousey"
    SET_DRAG_MODE = 613, // "sensing_setdragmode"
    LOUDNESS = 614, // "sensing_loudness"
    TIMER = 615, // "sensing_timer"
    RESET_TIMER = 616, // "sensing_resettimer"
    OF = 617, // "sensing_of"
    OF_MENU = 618, // "sensing_of_object_menu"
    CURRENT_TIME = 619, // "sensing_current"
    DAYS_SINCE_2000 = 620, // "sensing_dayssince2000"
    USERNAME = 621, // "sensing_username"
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

        // variables
        if (opcode == "data_setvariableto")
            return OPCODE::SET_VARIABLE_TO;
        if (opcode == "data_changevariableby")
            return OPCODE::CHANGE_VARIABLE_BY;

        // operators
        if (opcode == "operator_add")
            return OPCODE::OPERATOR_ADD;
        if (opcode == "operator_subtract")
            return OPCODE::OPERATOR_SUBTRACT;
        if (opcode == "operator_multiply")
            return OPCODE::OPERATOR_MULTIPLY;
        if (opcode == "operator_divide")
            return OPCODE::OPERATOR_DIVIDE;
        if (opcode == "operator_random")
            return OPCODE::OPERATOR_RANDOM;
        if (opcode == "operator_gt")
            return OPCODE::OPERATOR_GREATER_THAN;
        if (opcode == "operator_lt")
            return OPCODE::OPERATOR_LESS_THAN;
        if (opcode == "operator_equals")
            return OPCODE::OPERATOR_EQUALS;
        if (opcode == "operator_and")
            return OPCODE::OPERATOR_AND;
        if (opcode == "operator_or")
            return OPCODE::OPERATOR_OR;
        if (opcode == "operator_not")
            return OPCODE::OPERATOR_NOT;
        if (opcode == "operator_join")
            return OPCODE::OPERATOR_JOIN;
        if (opcode == "operator_letter_of")
            return OPCODE::OPERATOR_LETTER_OF;
        if (opcode == "operator_length")
            return OPCODE::OPERATOR_LENGTH;
        if (opcode == "operator_contains")
            return OPCODE::OPERATOR_CONTAINS;
        if (opcode == "operator_mod")
            return OPCODE::OPERATOR_MOD;
        if (opcode == "operator_round")
            return OPCODE::OPERATOR_ROUND;
        if (opcode == "operator_mathop")
            return OPCODE::OPERATOR_MATHOP;

        // control
        if (opcode == "control_wait")
            return OPCODE::WAIT;
        if (opcode == "control_repeat")
            return OPCODE::REPEAT;
        if (opcode == "control_forever")
            return OPCODE::FOREVER;
        if (opcode == "control_if")
            return OPCODE::IF;
        if (opcode == "control_if_else")
            return OPCODE::IF_ELSE;
        if (opcode == "control_wait_until")
            return OPCODE::WAIT_UNTIL;
        if (opcode == "control_repeat_until")
            return OPCODE::REPEAT_UNTIL;
        if (opcode == "control_stop")
            return OPCODE::STOP;
        if (opcode == "control_start_as_clone")
            return OPCODE::START_AS_CLONE;
        if (opcode == "control_create_clone_of")
            return OPCODE::CREATE_CLONE_OF;
        if (opcode == "control_delete_this_clone")
            return OPCODE::DELETE_THIS_CLONE;

        // sensing
        if (opcode == "sensing_touchingobject")
            return OPCODE::TOUCHING_OBJECT;
        if (opcode == "sensing_touchingobjectmenu")
            return OPCODE::TOUCHING_OBJECT_MENU;
        if (opcode == "sensing_touchingcolor")
            return OPCODE::TOUCHING_COLOR;
        if (opcode == "sensing_coloristouchingcolor")
            return OPCODE::COLOR_TOUCHING_COLOR;
        if (opcode == "sensing_distanceto")
            return OPCODE::DISTANCE_TO;
        if (opcode == "sensing_distancetomenu")
            return OPCODE::DISTANCE_TO_MENU;
        if (opcode == "sensing_askandwait")
            return OPCODE::ASK_AND_WAIT;
        if (opcode == "sensing_answer")
            return OPCODE::ANSWER;
        if (opcode == "sensing_keypressed")
            return OPCODE::KEY_PRESSED;
        if (opcode == "sensing_keyoptions")
            return OPCODE::KEY_OPTIONS;
        if (opcode == "sensing_mousedown")
            return OPCODE::MOUSE_DOWN;
        if (opcode == "sensing_mousex")
            return OPCODE::MOUSE_X;
        if (opcode == "sensing_mousey")
            return OPCODE::MOUSE_Y;
        if (opcode == "sensing_setdragmode")
            return OPCODE::SET_DRAG_MODE;
        if (opcode == "sensing_loudness")
            return OPCODE::LOUDNESS;
        if (opcode == "sensing_timer")
            return OPCODE::TIMER;
        if (opcode == "sensing_resettimer")
            return OPCODE::RESET_TIMER;
        if (opcode == "sensing_of")
            return OPCODE::OF;
        if (opcode == "sensing_of_object_menu")
            return OPCODE::OF_MENU;
        if (opcode == "sensing_current")
            return OPCODE::CURRENT_TIME;
        if (opcode == "sensing_dayssince2000")
            return OPCODE::DAYS_SINCE_2000;
        if (opcode == "sensing_username")
            return OPCODE::USERNAME;

        // special
        if (opcode == "variable")
            return OPCODE::VARIABLE;

        std::cout << "unknown opcode detected: '" << opcode << "'" << std::endl;
        return OPCODE::UNKNOWN;
    }
};