#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

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
    SIZE_VAL = 219, // "looks_size"

    // Variables and Lists
    SET_VARIABLE_TO = 300, // "data_setvariableto"
    CHANGE_VARIABLE_BY = 301, // "data_changevariableby"
    SHOW_VARIABLE = 302, // "data_showvariable"
    HIDE_VARIABLE = 303, // "data_hidevariable"
    ADD_TO_LIST = 304, // "data_addtolist"
    DELETE_OF = 305, // "data_deleteoflist"
    DELETE_ALL = 306, // "data_deletealloflist"
    INSERT_AT = 307, // "data_insertatlist"
    REPLACE_ITEM = 308, // "data_replaceitemoflist"
    LIST_ITEM = 309, // "data_itemoflist"
    ITEM_NUM_IN_LIST = 310, // "data_itemnumoflist"
    LIST_LENGTH = 311, // "data_lengthoflist"
    LIST_CONTAINS = 312, // "data_listcontainsitem"
    SHOW_LIST = 313, // "data_showlist"
    HIDE_LIST = 314, // "data_hidelist"

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

const std::unordered_map<std::string, OPCODE> opcodeenum {
    {"event_whenflagclicked", OPCODE::WHEN_FLAG_CLICKED},
    {"event_whenkeypressed", OPCODE::WHEN_KEY_PRESSED},
    {"event_whenthisspriteclicked", OPCODE::WHEN_THIS_SPRITE_CLICKED},
    {"event_whengreaterthan", OPCODE::WHEN_GREATER_THAN},
    {"event_whenbroadcastreceived", OPCODE::WHEN_BROADCAST_RECEIVED},
    {"event_broadcast", OPCODE::BROADCAST},
    {"event_broadcastandwait", OPCODE::BROADCAST_AND_WAIT},

    {"motion_movesteps", OPCODE::MOVE_STEPS},
    {"motion_turnright", OPCODE::TURN_RIGHT},
    {"motion_turnleft", OPCODE::TURN_LEFT},
    {"motion_goto", OPCODE::GO_TO},
    {"motion_gotoxy", OPCODE::GO_TO_XY},
    {"motion_glideto", OPCODE::GLIDE_TO},
    {"motion_glidesecstoxy", OPCODE::GLIDE_TO_XY},
    {"motion_pointindirection", OPCODE::POINT_IN_DIRECTION},
    {"motion_pointtowards", OPCODE::POINT_TOWARDS},
    {"motion_changexby", OPCODE::CHANGE_X_BY},
    {"motion_setx", OPCODE::SET_X_TO},
    {"motion_changeyby", OPCODE::CHANGE_Y_BY},
    {"motion_sety", OPCODE::SET_Y_TO},
    {"motion_ifonedgebounce", OPCODE::IF_ON_EDGE_BOUNCE},
    {"motion_setrotationstyle", OPCODE::SET_ROTATION_STYLE},
    {"motion_xposition", OPCODE::X_POS},
    {"motion_yposition", OPCODE::Y_POS},
    {"motion_direction", OPCODE::DIRECTION},

    {"looks_sayforsecs", OPCODE::SAY_FOR_SECS},
    {"looks_say", OPCODE::SAY},
    {"looks_thinkforsecs", OPCODE::THINK_FOR_SECS},
    {"looks_think", OPCODE::THINK},
    {"looks_switchcostumeto", OPCODE::SWITCH_TO_COSTUME},
    {"looks_nextcostume", OPCODE::NEXT_COSTUME},
    {"looks_switchbackdropto", OPCODE::SWITCH_TO_BACKDROP},
    {"looks_nextbackdrop", OPCODE::NEXT_BACKDROP},
    {"looks_changesizeby", OPCODE::CHANGE_SIZE_BY},
    {"looks_setsizeto", OPCODE::SET_SIZE_TO},
    {"looks_changeeffectby", OPCODE::CHANGE_EFFECT_BY},
    {"looks_seteffectto", OPCODE::SET_EFFECT_TO},
    {"looks_cleargraphiceffects", OPCODE::CLEAR_GRAPHIC_EFFECTS},
    {"looks_show", OPCODE::SHOW},
    {"looks_hide", OPCODE::HIDE},
    {"looks_gotofrontback", OPCODE::GO_TO_LAYER},
    {"looks_goforwardbackwardlayers", OPCODE::CHANGE_LAYER_BY},
    {"looks_costumenumbername", OPCODE::COSTUME_NUM_NAME},
    {"looks_backdropnumbername", OPCODE::BACKDROP_NUM_NAME},
    {"looks_size", OPCODE::SIZE_VAL},

    {"data_setvariableto", OPCODE::SET_VARIABLE_TO},
    {"data_changevariableby", OPCODE::CHANGE_VARIABLE_BY},
    {"data_addtolist", OPCODE::ADD_TO_LIST},
    {"data_insertatlist", OPCODE::INSERT_AT},
    {"data_deleteoflist", OPCODE::DELETE_OF},
    {"data_deletealloflist", OPCODE::DELETE_ALL},
    {"data_replaceitemoflist", OPCODE::REPLACE_ITEM},
    {"data_itemoflist", OPCODE::LIST_ITEM},
    {"data_itemnumoflist", OPCODE::ITEM_NUM_IN_LIST},
    {"data_lengthoflist", OPCODE::LIST_LENGTH},
    {"data_listcontainsitem", OPCODE::LIST_CONTAINS},
    {"data_showlist", OPCODE::SHOW_LIST},
    {"data_hidelist", OPCODE::HIDE_LIST},

    {"operator_add", OPCODE::OPERATOR_ADD},
    {"operator_subtract", OPCODE::OPERATOR_SUBTRACT},
    {"operator_multiply", OPCODE::OPERATOR_MULTIPLY},
    {"operator_divide", OPCODE::OPERATOR_DIVIDE},
    {"operator_random", OPCODE::OPERATOR_RANDOM},
    {"operator_gt", OPCODE::OPERATOR_GREATER_THAN},
    {"operator_lt", OPCODE::OPERATOR_LESS_THAN},
    {"operator_equals", OPCODE::OPERATOR_EQUALS},
    {"operator_and", OPCODE::OPERATOR_AND},
    {"operator_or", OPCODE::OPERATOR_OR},
    {"operator_not", OPCODE::OPERATOR_NOT},
    {"operator_join", OPCODE::OPERATOR_JOIN},
    {"operator_letter_of", OPCODE::OPERATOR_LETTER_OF},
    {"operator_length", OPCODE::OPERATOR_LENGTH},
    {"operator_contains", OPCODE::OPERATOR_CONTAINS},
    {"operator_mod", OPCODE::OPERATOR_MOD},
    {"operator_round", OPCODE::OPERATOR_ROUND},
    {"operator_mathop", OPCODE::OPERATOR_MATHOP},

    {"control_wait", OPCODE::WAIT},
    {"control_repeat", OPCODE::REPEAT},
    {"control_forever", OPCODE::FOREVER},
    {"control_wait_until", OPCODE::WAIT_UNTIL},
    {"control_if", OPCODE::IF},
    {"control_if_else", OPCODE::IF_ELSE},
    {"control_repeat_until", OPCODE::REPEAT_UNTIL},
    {"control_stop", OPCODE::STOP},
    {"control_start_as_clone", OPCODE::START_AS_CLONE},
    {"control_create_clone_of", OPCODE::CREATE_CLONE_OF},
    {"control_delete_this_clone", OPCODE::DELETE_THIS_CLONE},

    {"sensing_touchingobject", OPCODE::TOUCHING_OBJECT},
    {"sensing_touchingobjectmenu", OPCODE::TOUCHING_OBJECT_MENU},
    {"sensing_touchingcolor", OPCODE::TOUCHING_COLOR},
    {"sensing_coloristouchingcolor", OPCODE::COLOR_TOUCHING_COLOR},
    {"sensing_distanceto", OPCODE::DISTANCE_TO},
    {"sensing_distancetomenu", OPCODE::DISTANCE_TO_MENU},
    {"sensing_askandwait", OPCODE::ASK_AND_WAIT},
    {"sensing_answer", OPCODE::ANSWER},
    {"sensing_keypressed", OPCODE::KEY_PRESSED},
    {"sensing_keyoptions", OPCODE::KEY_OPTIONS},
    {"sensing_mousedown", OPCODE::MOUSE_DOWN},
    {"sensing_mousex", OPCODE::MOUSE_X},
    {"sensing_mousey", OPCODE::MOUSE_Y},
    {"sensing_setdragmode", OPCODE::SET_DRAG_MODE},
    {"sensing_loudness", OPCODE::LOUDNESS},
    {"sensing_timer", OPCODE::TIMER},
    {"sensing_resettimer", OPCODE::RESET_TIMER},
    {"sensing_of", OPCODE::OF},
    {"sensing_of_object_menu", OPCODE::OF_MENU},
    {"sensing_current", OPCODE::CURRENT_TIME},
    {"sensing_dayssince2000", OPCODE::DAYS_SINCE_2000},
    {"sensing_username", OPCODE::USERNAME},

    {"variable", OPCODE::VARIABLE}
};

class Opcodes {
public:
    static OPCODE opcode_to_enum(std::string opcode) {
        try {
            return opcodeenum.at(opcode);
        } catch(std::exception e) {
            std::cout << "unknown opcode detected: '" << opcode << "'" << std::endl;
            return OPCODE::UNKNOWN;
        }
    }
};