#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

enum OPTYPE { BLOCK, REPORTER, CONDITIONAL, SHADOW };

enum OPCODE {
    LIST_REPORTER = -3,
    VARIABLE_REPORTER = -2,
    UNKNOWN = -1,

    // Event Blocks
    WHEN_FLAG_CLICKED = 0,         // "event_whenflagclicked"
    WHEN_KEY_PRESSED = 1,          // "event_whenkeypressed"
    WHEN_THIS_SPRITE_CLICKED = 2,  // "event_whenthisspriteclicked"
    WHEN_GREATER_THAN = 3,         // "event_whengreaterthan"
    WHEN_BROADCAST_RECEIVED = 4,   // "event_whenbroadcastreceived"
    BROADCAST = 5,                 // "event_broadcast"
    BROADCAST_AND_WAIT = 6,        // "event_broadcastandwait"

    // Motion Blocks
    MOVE_STEPS = 100,          // "motion_movesteps"
    TURN_RIGHT = 101,          // "motion_turnright"
    TURN_LEFT = 102,           // "motion_turnleft"
    GO_TO = 103,               // "motion_goto"
    GO_TO_XY = 104,            // "motion_gotoxy"
    GLIDE_TO = 105,            // "motion_glideto"
    GLIDE_TO_XY = 106,         // "motion_glidesecstoxy"
    POINT_IN_DIRECTION = 107,  // "motion_pointindirection"
    POINT_TOWARDS = 108,       // "motion_pointtowards"
    CHANGE_X_BY = 109,         // "motion_changexby"
    SET_X_TO = 110,            // "motion_setx"
    CHANGE_Y_BY = 111,         // "motion_changeyby"
    SET_Y_TO = 112,            // "motion_sety"
    IF_ON_EDGE_BOUNCE = 113,   // "motion_ifonedgebounce"
    SET_ROTATION_STYLE = 114,  // "motion_setrotationstyle"
    X_POS = 115,               // "motion_xposition"
    Y_POS = 116,               // "motion_yposition"
    DIRECTION = 117,           // "motion_direction"
    GO_TO_MENU = 118,          // "motion_goto_menu"
    GLIDE_TO_MENU = 119,       // "motion_glideto_menu"
    POINT_TOWARDS_MENU = 120,  // "motion_pointtowards_menu"

    // Looks Blocks
    SAY_FOR_SECS = 200,           // "looks_sayforsecs"
    SAY = 201,                    // "looks_say"
    THINK_FOR_SECS = 202,         // "looks_thinkforsecs"
    THINK = 203,                  // "looks_think"
    SWITCH_TO_COSTUME = 204,      // "looks_switchcostumeto"
    NEXT_COSTUME = 205,           // "looks_nextcostume"
    SWITCH_TO_BACKDROP = 206,     // "looks_switchbackdropto"
    NEXT_BACKDROP = 207,          // "looks_nextbackdrop"
    CHANGE_SIZE_BY = 208,         // "looks_changesizeby"
    SET_SIZE_TO = 209,            // "looks_setsizeto"
    CHANGE_EFFECT_BY = 210,       // "looks_changeeffectby"
    SET_EFFECT_TO = 211,          // "looks_seteffectto"
    CLEAR_GRAPHIC_EFFECTS = 212,  // "looks_cleargraphiceffects"
    SHOW = 213,                   // "looks_show"
    HIDE = 214,                   // "looks_hide"
    GO_TO_LAYER = 215,            // "looks_gotofrontback"
    CHANGE_LAYER_BY = 216,        // "looks_goforwardbackwardlayers"
    COSTUME_NUM_NAME = 217,       // "looks_costumenumbername"
    BACKDROP_NUM_NAME = 218,      // "looks_backdropnumbername"
    SIZE_VAL = 219,               // "looks_size"
    COSTUME = 220,                // "looks_costume"

    // Variables and Lists
    SET_VARIABLE_TO = 300,     // "data_setvariableto"
    CHANGE_VARIABLE_BY = 301,  // "data_changevariableby"
    SHOW_VARIABLE = 302,       // "data_showvariable"
    HIDE_VARIABLE = 303,       // "data_hidevariable"
    ADD_TO_LIST = 304,         // "data_addtolist"
    DELETE_OF = 305,           // "data_deleteoflist"
    DELETE_ALL = 306,          // "data_deletealloflist"
    INSERT_AT = 307,           // "data_insertatlist"
    REPLACE_ITEM = 308,        // "data_replaceitemoflist"
    LIST_ITEM = 309,           // "data_itemoflist"
    ITEM_NUM_IN_LIST = 310,    // "data_itemnumoflist"
    LIST_LENGTH = 311,         // "data_lengthoflist"
    LIST_CONTAINS = 312,       // "data_listcontainsitem"
    SHOW_LIST = 313,           // "data_showlist"
    HIDE_LIST = 314,           // "data_hidelist"

    // Operator Symbols
    OPERATOR_ADD = 400,           // "operator_add"
    OPERATOR_SUBTRACT = 401,      // "operator_subtract"
    OPERATOR_MULTIPLY = 402,      // "operator_multiply"
    OPERATOR_DIVIDE = 403,        // "operator_divide"
    OPERATOR_RANDOM = 404,        // "operator_random"
    OPERATOR_GREATER_THAN = 405,  // "operator_gt"
    OPERATOR_LESS_THAN = 406,     // "operator_lt"
    OPERATOR_EQUALS = 407,        // "operator_equals"
    OPERATOR_AND = 408,           // "operator_and"
    OPERATOR_OR = 409,            // "operator_or"
    OPERATOR_NOT = 410,           // "operator_not"
    OPERATOR_JOIN = 411,          // "operator_join"
    OPERATOR_LETTER_OF = 412,     // "operator_letter_of"
    OPERATOR_LENGTH = 413,        // "operator_length"
    OPERATOR_CONTAINS = 414,      // "operator_contains"
    OPERATOR_MOD = 415,           // "operator_mod"
    OPERATOR_ROUND = 416,         // "operator_round"
    OPERATOR_MATHOP = 417,        // "operator_mathop"

    // Control Blocks
    WAIT = 500,                  // "control_wait"
    REPEAT = 501,                // "control_repeat"
    FOREVER = 502,               // "control_forever"
    IF = 503,                    // "control_if"
    IF_ELSE = 504,               // "control_if_else"
    WAIT_UNTIL = 505,            // "control_wait_until"
    REPEAT_UNTIL = 506,          // "control_repeat_until"
    STOP = 507,                  // "control_stop"
    START_AS_CLONE = 508,        // "control_start_as_clone"
    CREATE_CLONE_OF = 509,       // "control_create_clone_of"
    CREATE_CLONE_OF_MENU = 510,  // "control_create_clone_of_menu"
    DELETE_THIS_CLONE = 511,     // "control_delete_this_clone"

    // Sensing Blocks
    TOUCHING_OBJECT = 600,       // "sensing_touchingobject"
    TOUCHING_OBJECT_MENU = 601,  // "sensing_touchingobjectmenu"
    TOUCHING_COLOR = 602,        // "sensing_touchingcolor"
    COLOR_TOUCHING_COLOR = 603,  // "sensing_coloristouchingcolor"
    DISTANCE_TO = 604,           // "sensing_distanceto"
    DISTANCE_TO_MENU = 605,      // "sensing_distancetomenu"
    ASK_AND_WAIT = 606,          // "sensing_askandwait"
    ANSWER = 607,                // "sensing_answer"
    KEY_PRESSED = 608,           // "sensing_keypressed"
    KEY_OPTIONS = 609,           // "sensing_keyoptions"
    MOUSE_DOWN = 610,            // "sensing_mousedown"
    MOUSE_X = 611,               // "sensing_mousex"
    MOUSE_Y = 612,               // "sensing_mousey"
    SET_DRAG_MODE = 613,         // "sensing_setdragmode"
    LOUDNESS = 614,              // "sensing_loudness"
    TIMER = 615,                 // "sensing_timer"
    RESET_TIMER = 616,           // "sensing_resettimer"
    OF = 617,                    // "sensing_of"
    OF_MENU = 618,               // "sensing_of_object_menu"
    CURRENT_TIME = 619,          // "sensing_current"
    DAYS_SINCE_2000 = 620,       // "sensing_dayssince2000"
    USERNAME = 621,              // "sensing_username"

    // Sound Blocks
    PLAY_UNTIL_DONE = 700,         // "sound_playuntildone"
    SOUNDS_MENU = 701,             // "sound_sounds_menu"
    PLAY = 702,                    // "sound_play"
    STOP_ALL_SOUNDS = 703,         // "sound_stopallsounds"
    CHANGE_SOUND_EFFECT_BY = 704,  // "sound_changeeffectby"
    SET_SOUND_EFFECT_TO = 705,     // "sound_seteffectto"
    CLEAR_SOUND_EFFECTS = 706,     // "sound_cleareffects"
    CHANGE_VOLUME_BY = 707,        // "sound_changevolumeby"
    SET_VOLUME_TO = 708,           // "sound_setvolumeto"
    VOLUME = 709,                  // "sound_volume"

    // Procedure Blocks
    ARG_STRING_NUM = 800,  // "argument_reporter_string_number"
    ARG_BOOLEAN = 801,     // "argument_reporter_boolean"
    DEFINITION = 802,      // "procedures_definition"
    PROTOTYPE = 803,       // "procedures_prototype"
    CALL = 804,            // "procedures_call"

    // Pen Blocks
    SET_PEN_COLOR_TO = 901,        // "pen_setPenColorParamTo"
    CHANGE_PEN_COLOR_BY = 902,     // "pen_changePenColorParamBy"
    SET_PEN_COLOR_TO_COLOR = 903,  // "pen_setPenColorToColor"
    CHANGE_PEN_SIZE_BY = 904,      // "pen_changePenSizeBy"
    SET_PEN_SIZE_TO = 905,         // "pen_setPenSizeTo"
    PEN_STAMP = 906,               // "pen_stamp"
    PEN_CLEAR = 907,               // "pen_clear"
    PEN_COLOR_PARAM_MENU = 908,    // "pen_menu_colorParam"
    PEN_UP = 909,                  // "pen_penUp"
    PEN_DOWN = 910,                // "pen_penDown"
};

struct OPCODETYPE {
    OPCODE opcode;
    OPTYPE optype;

    OPCODETYPE(OPCODE opc, OPTYPE opt) {
        opcode = opc;
        optype = opt;
    }

    operator OPCODE() { return opcode; }
    operator OPTYPE() { return optype; }
};

const std::unordered_map<std::string, OPCODETYPE> opcodeenum{
    {"event_whenflagclicked", OPCODETYPE(OPCODE::WHEN_FLAG_CLICKED, OPTYPE::BLOCK)},
    {"event_whenkeypressed", OPCODETYPE(OPCODE::WHEN_KEY_PRESSED, OPTYPE::BLOCK)},
    {"event_whenthisspriteclicked", OPCODETYPE(OPCODE::WHEN_THIS_SPRITE_CLICKED, OPTYPE::BLOCK)},
    {"event_whengreaterthan", OPCODETYPE(OPCODE::WHEN_GREATER_THAN, OPTYPE::BLOCK)},
    {"event_whenbroadcastreceived", OPCODETYPE(OPCODE::WHEN_BROADCAST_RECEIVED, OPTYPE::BLOCK)},
    {"event_broadcast", OPCODETYPE(OPCODE::BROADCAST, OPTYPE::BLOCK)},
    {"event_broadcastandwait", OPCODETYPE(OPCODE::BROADCAST_AND_WAIT, OPTYPE::BLOCK)},

    {"motion_movesteps", OPCODETYPE(OPCODE::MOVE_STEPS, OPTYPE::BLOCK)},
    {"motion_turnright", OPCODETYPE(OPCODE::TURN_RIGHT, OPTYPE::BLOCK)},
    {"motion_turnleft", OPCODETYPE(OPCODE::TURN_LEFT, OPTYPE::BLOCK)},
    {"motion_goto", OPCODETYPE(OPCODE::GO_TO, OPTYPE::BLOCK)},
    {"motion_goto_menu", OPCODETYPE(OPCODE::GO_TO_MENU, OPTYPE::SHADOW)},
    {"motion_gotoxy", OPCODETYPE(OPCODE::GO_TO_XY, OPTYPE::BLOCK)},
    {"motion_glideto", OPCODETYPE(OPCODE::GLIDE_TO, OPTYPE::BLOCK)},
    {"motion_glideto_menu", OPCODETYPE(OPCODE::GLIDE_TO_MENU, OPTYPE::SHADOW)},
    {"motion_glidesecstoxy", OPCODETYPE(OPCODE::GLIDE_TO_XY, OPTYPE::BLOCK)},
    {"motion_pointindirection", OPCODETYPE(OPCODE::POINT_IN_DIRECTION, OPTYPE::BLOCK)},
    {"motion_pointtowards", OPCODETYPE(OPCODE::POINT_TOWARDS, OPTYPE::BLOCK)},
    {"motion_pointtowards_menu", OPCODETYPE(OPCODE::POINT_TOWARDS_MENU, OPTYPE::SHADOW)},
    {"motion_changexby", OPCODETYPE(OPCODE::CHANGE_X_BY, OPTYPE::BLOCK)},
    {"motion_setx", OPCODETYPE(OPCODE::SET_X_TO, OPTYPE::BLOCK)},
    {"motion_changeyby", OPCODETYPE(OPCODE::CHANGE_Y_BY, OPTYPE::BLOCK)},
    {"motion_sety", OPCODETYPE(OPCODE::SET_Y_TO, OPTYPE::BLOCK)},
    {"motion_ifonedgebounce", OPCODETYPE(OPCODE::IF_ON_EDGE_BOUNCE, OPTYPE::BLOCK)},
    {"motion_setrotationstyle", OPCODETYPE(OPCODE::SET_ROTATION_STYLE, OPTYPE::BLOCK)},
    {"motion_xposition", OPCODETYPE(OPCODE::X_POS, OPTYPE::REPORTER)},
    {"motion_yposition", OPCODETYPE(OPCODE::Y_POS, OPTYPE::REPORTER)},
    {"motion_direction", OPCODETYPE(OPCODE::DIRECTION, OPTYPE::REPORTER)},

    {"looks_sayforsecs", OPCODETYPE(OPCODE::SAY_FOR_SECS, OPTYPE::BLOCK)},
    {"looks_say", OPCODETYPE(OPCODE::SAY, OPTYPE::BLOCK)},
    {"looks_thinkforsecs", OPCODETYPE(OPCODE::THINK_FOR_SECS, OPTYPE::BLOCK)},
    {"looks_think", OPCODETYPE(OPCODE::THINK, OPTYPE::BLOCK)},
    {"looks_switchcostumeto", OPCODETYPE(OPCODE::SWITCH_TO_COSTUME, OPTYPE::BLOCK)},
    {"looks_nextcostume", OPCODETYPE(OPCODE::NEXT_COSTUME, OPTYPE::BLOCK)},
    {"looks_switchbackdropto", OPCODETYPE(OPCODE::SWITCH_TO_BACKDROP, OPTYPE::BLOCK)},
    {"looks_nextbackdrop", OPCODETYPE(OPCODE::NEXT_BACKDROP, OPTYPE::BLOCK)},
    {"looks_changesizeby", OPCODETYPE(OPCODE::CHANGE_SIZE_BY, OPTYPE::BLOCK)},
    {"looks_setsizeto", OPCODETYPE(OPCODE::SET_SIZE_TO, OPTYPE::BLOCK)},
    {"looks_changeeffectby", OPCODETYPE(OPCODE::CHANGE_EFFECT_BY, OPTYPE::BLOCK)},
    {"looks_seteffectto", OPCODETYPE(OPCODE::SET_EFFECT_TO, OPTYPE::BLOCK)},
    {"looks_cleargraphiceffects", OPCODETYPE(OPCODE::CLEAR_GRAPHIC_EFFECTS, OPTYPE::BLOCK)},
    {"looks_show", OPCODETYPE(OPCODE::SHOW, OPTYPE::BLOCK)},
    {"looks_hide", OPCODETYPE(OPCODE::HIDE, OPTYPE::BLOCK)},
    {"looks_gotofrontback", OPCODETYPE(OPCODE::GO_TO_LAYER, OPTYPE::BLOCK)},
    {"looks_goforwardbackwardlayers", OPCODETYPE(OPCODE::CHANGE_LAYER_BY, OPTYPE::BLOCK)},
    {"looks_costumenumbername", OPCODETYPE(OPCODE::COSTUME_NUM_NAME, OPTYPE::REPORTER)},
    {"looks_backdropnumbername", OPCODETYPE(OPCODE::BACKDROP_NUM_NAME, OPTYPE::REPORTER)},
    {"looks_size", OPCODETYPE(OPCODE::SIZE_VAL, OPTYPE::REPORTER)},
    {"looks_costume", OPCODETYPE(OPCODE::COSTUME, OPTYPE::SHADOW)},

    {"data_setvariableto", OPCODETYPE(OPCODE::SET_VARIABLE_TO, OPTYPE::BLOCK)},
    {"data_changevariableby", OPCODETYPE(OPCODE::CHANGE_VARIABLE_BY, OPTYPE::BLOCK)},
    {"data_showvariable", OPCODETYPE(OPCODE::SHOW_VARIABLE, OPTYPE::BLOCK)},
    {"data_hidevariable", OPCODETYPE(OPCODE::HIDE_VARIABLE, OPTYPE::BLOCK)},
    {"data_addtolist", OPCODETYPE(OPCODE::ADD_TO_LIST, OPTYPE::BLOCK)},
    {"data_insertatlist", OPCODETYPE(OPCODE::INSERT_AT, OPTYPE::BLOCK)},
    {"data_deleteoflist", OPCODETYPE(OPCODE::DELETE_OF, OPTYPE::BLOCK)},
    {"data_deletealloflist", OPCODETYPE(OPCODE::DELETE_ALL, OPTYPE::BLOCK)},
    {"data_replaceitemoflist", OPCODETYPE(OPCODE::REPLACE_ITEM, OPTYPE::BLOCK)},
    {"data_itemoflist", OPCODETYPE(OPCODE::LIST_ITEM, OPTYPE::REPORTER)},
    {"data_itemnumoflist", OPCODETYPE(OPCODE::ITEM_NUM_IN_LIST, OPTYPE::REPORTER)},
    {"data_lengthoflist", OPCODETYPE(OPCODE::LIST_LENGTH, OPTYPE::REPORTER)},
    {"data_listcontainsitem", OPCODETYPE(OPCODE::LIST_CONTAINS, OPTYPE::CONDITIONAL)},
    {"data_showlist", OPCODETYPE(OPCODE::SHOW_LIST, OPTYPE::BLOCK)},
    {"data_hidelist", OPCODETYPE(OPCODE::HIDE_LIST, OPTYPE::BLOCK)},

    {"operator_add", OPCODETYPE(OPCODE::OPERATOR_ADD, OPTYPE::REPORTER)},
    {"operator_subtract", OPCODETYPE(OPCODE::OPERATOR_SUBTRACT, OPTYPE::REPORTER)},
    {"operator_multiply", OPCODETYPE(OPCODE::OPERATOR_MULTIPLY, OPTYPE::REPORTER)},
    {"operator_divide", OPCODETYPE(OPCODE::OPERATOR_DIVIDE, OPTYPE::REPORTER)},
    {"operator_random", OPCODETYPE(OPCODE::OPERATOR_RANDOM, OPTYPE::REPORTER)},
    {"operator_gt", OPCODETYPE(OPCODE::OPERATOR_GREATER_THAN, OPTYPE::CONDITIONAL)},
    {"operator_lt", OPCODETYPE(OPCODE::OPERATOR_LESS_THAN, OPTYPE::CONDITIONAL)},
    {"operator_equals", OPCODETYPE(OPCODE::OPERATOR_EQUALS, OPTYPE::CONDITIONAL)},
    {"operator_and", OPCODETYPE(OPCODE::OPERATOR_AND, OPTYPE::CONDITIONAL)},
    {"operator_or", OPCODETYPE(OPCODE::OPERATOR_OR, OPTYPE::CONDITIONAL)},
    {"operator_not", OPCODETYPE(OPCODE::OPERATOR_NOT, OPTYPE::CONDITIONAL)},
    {"operator_join", OPCODETYPE(OPCODE::OPERATOR_JOIN, OPTYPE::REPORTER)},
    {"operator_letter_of", OPCODETYPE(OPCODE::OPERATOR_LETTER_OF, OPTYPE::REPORTER)},
    {"operator_length", OPCODETYPE(OPCODE::OPERATOR_LENGTH, OPTYPE::REPORTER)},
    {"operator_contains", OPCODETYPE(OPCODE::OPERATOR_CONTAINS, OPTYPE::CONDITIONAL)},
    {"operator_mod", OPCODETYPE(OPCODE::OPERATOR_MOD, OPTYPE::REPORTER)},
    {"operator_round", OPCODETYPE(OPCODE::OPERATOR_ROUND, OPTYPE::REPORTER)},
    {"operator_mathop", OPCODETYPE(OPCODE::OPERATOR_MATHOP, OPTYPE::REPORTER)},

    {"control_wait", OPCODETYPE(OPCODE::WAIT, OPTYPE::BLOCK)},
    {"control_repeat", OPCODETYPE(OPCODE::REPEAT, OPTYPE::BLOCK)},
    {"control_forever", OPCODETYPE(OPCODE::FOREVER, OPTYPE::BLOCK)},
    {"control_wait_until", OPCODETYPE(OPCODE::WAIT_UNTIL, OPTYPE::BLOCK)},
    {"control_if", OPCODETYPE(OPCODE::IF, OPTYPE::BLOCK)},
    {"control_if_else", OPCODETYPE(OPCODE::IF_ELSE, OPTYPE::BLOCK)},
    {"control_repeat_until", OPCODETYPE(OPCODE::REPEAT_UNTIL, OPTYPE::BLOCK)},
    {"control_stop", OPCODETYPE(OPCODE::STOP, OPTYPE::BLOCK)},
    {"control_start_as_clone", OPCODETYPE(OPCODE::START_AS_CLONE, OPTYPE::BLOCK)},
    {"control_create_clone_of", OPCODETYPE(OPCODE::CREATE_CLONE_OF, OPTYPE::BLOCK)},
    {"control_create_clone_of_menu", OPCODETYPE(OPCODE::CREATE_CLONE_OF_MENU, OPTYPE::SHADOW)},
    {"control_delete_this_clone", OPCODETYPE(OPCODE::DELETE_THIS_CLONE, OPTYPE::BLOCK)},

    {"sensing_touchingobject", OPCODETYPE(OPCODE::TOUCHING_OBJECT, OPTYPE::CONDITIONAL)},
    {"sensing_touchingobjectmenu", OPCODETYPE(OPCODE::TOUCHING_OBJECT_MENU, OPTYPE::SHADOW)},
    {"sensing_touchingcolor", OPCODETYPE(OPCODE::TOUCHING_COLOR, OPTYPE::CONDITIONAL)},
    {"sensing_coloristouchingcolor", OPCODETYPE(OPCODE::COLOR_TOUCHING_COLOR, OPTYPE::CONDITIONAL)},
    {"sensing_distanceto", OPCODETYPE(OPCODE::DISTANCE_TO, OPTYPE::REPORTER)},
    {"sensing_distancetomenu", OPCODETYPE(OPCODE::DISTANCE_TO_MENU, OPTYPE::SHADOW)},
    {"sensing_askandwait", OPCODETYPE(OPCODE::ASK_AND_WAIT, OPTYPE::BLOCK)},
    {"sensing_answer", OPCODETYPE(OPCODE::ANSWER, OPTYPE::REPORTER)},
    {"sensing_keypressed", OPCODETYPE(OPCODE::KEY_PRESSED, OPTYPE::CONDITIONAL)},
    {"sensing_keyoptions", OPCODETYPE(OPCODE::KEY_OPTIONS, OPTYPE::CONDITIONAL)},
    {"sensing_mousedown", OPCODETYPE(OPCODE::MOUSE_DOWN, OPTYPE::CONDITIONAL)},
    {"sensing_mousex", OPCODETYPE(OPCODE::MOUSE_X, OPTYPE::REPORTER)},
    {"sensing_mousey", OPCODETYPE(OPCODE::MOUSE_Y, OPTYPE::REPORTER)},
    {"sensing_setdragmode", OPCODETYPE(OPCODE::SET_DRAG_MODE, OPTYPE::BLOCK)},
    {"sensing_loudness", OPCODETYPE(OPCODE::LOUDNESS, OPTYPE::REPORTER)},
    {"sensing_timer", OPCODETYPE(OPCODE::TIMER, OPTYPE::REPORTER)},
    {"sensing_resettimer", OPCODETYPE(OPCODE::RESET_TIMER, OPTYPE::BLOCK)},
    {"sensing_of", OPCODETYPE(OPCODE::OF, OPTYPE::REPORTER)},
    {"sensing_of_object_menu", OPCODETYPE(OPCODE::OF_MENU, OPTYPE::SHADOW)},
    {"sensing_current", OPCODETYPE(OPCODE::CURRENT_TIME, OPTYPE::REPORTER)},
    {"sensing_dayssince2000", OPCODETYPE(OPCODE::DAYS_SINCE_2000, OPTYPE::REPORTER)},
    {"sensing_username", OPCODETYPE(OPCODE::USERNAME, OPTYPE::REPORTER)},

    {"sound_playuntildone", OPCODETYPE(OPCODE::PLAY_UNTIL_DONE, OPTYPE::BLOCK)},
    {"sound_sounds_menu", OPCODETYPE(OPCODE::SOUNDS_MENU, OPTYPE::SHADOW)},
    {"sound_play", OPCODETYPE(OPCODE::PLAY, OPTYPE::BLOCK)},
    {"sound_stopallsounds", OPCODETYPE(OPCODE::STOP_ALL_SOUNDS, OPTYPE::BLOCK)},
    {"sound_changeeffectby", OPCODETYPE(OPCODE::CHANGE_EFFECT_BY, OPTYPE::BLOCK)},
    {"sound_seteffectto", OPCODETYPE(OPCODE::SET_EFFECT_TO, OPTYPE::BLOCK)},
    {"sound_cleareffects", OPCODETYPE(OPCODE::CLEAR_SOUND_EFFECTS, OPTYPE::BLOCK)},
    {"sound_changevolumeby", OPCODETYPE(OPCODE::CHANGE_VOLUME_BY, OPTYPE::BLOCK)},
    {"sound_setvolumeto", OPCODETYPE(OPCODE::SET_VOLUME_TO, OPTYPE::BLOCK)},
    {"sound_volume", OPCODETYPE(OPCODE::VOLUME, OPTYPE::REPORTER)},

    {"argument_reporter_string_number", OPCODETYPE(OPCODE::ARG_STRING_NUM, OPTYPE::REPORTER)},
    {"argument_reporter_boolean", OPCODETYPE(OPCODE::ARG_BOOLEAN, OPTYPE::CONDITIONAL)},
    {"procedures_definition", OPCODETYPE(OPCODE::DEFINITION, OPTYPE::BLOCK)},
    {"procedures_prototype", OPCODETYPE(OPCODE::PROTOTYPE, OPTYPE::SHADOW)},
    {"procedures_call", OPCODETYPE(OPCODE::CALL, OPTYPE::BLOCK)},

    {"pen_setPenColorParamTo", OPCODETYPE(OPCODE::SET_PEN_COLOR_TO, OPTYPE::BLOCK)},
    {"pen_changePenColorParamBy", OPCODETYPE(OPCODE::CHANGE_PEN_COLOR_BY, OPTYPE::BLOCK)},
    {"pen_setPenColorToColor", OPCODETYPE(OPCODE::SET_PEN_COLOR_TO_COLOR, OPTYPE::BLOCK)},
    {"pen_changePenSizeBy", OPCODETYPE(OPCODE::CHANGE_PEN_SIZE_BY, OPTYPE::BLOCK)},
    {"pen_setPenSizeTo", OPCODETYPE(OPCODE::SET_PEN_SIZE_TO, OPTYPE::BLOCK)},
    {"pen_stamp", OPCODETYPE(OPCODE::PEN_STAMP, OPTYPE::BLOCK)},
    {"pen_clear", OPCODETYPE(OPCODE::PEN_CLEAR, OPTYPE::BLOCK)},
    {"pen_menu_colorParam", OPCODETYPE(OPCODE::PEN_COLOR_PARAM_MENU, OPTYPE::BLOCK)},
    {"pen_penUp", OPCODETYPE(OPCODE::PEN_UP, OPTYPE::BLOCK)},
    {"pen_penDown", OPCODETYPE(OPCODE::PEN_DOWN, OPTYPE::BLOCK)},

    {"variable", OPCODETYPE(OPCODE::VARIABLE_REPORTER, OPTYPE::REPORTER)},
    {"list", OPCODETYPE(OPCODE::LIST_REPORTER, OPTYPE::REPORTER)}};

class Opcodes {
public:
    static OPCODETYPE opcode_to_enum(std::string opcode) {
        try {
            return opcodeenum.at(opcode);
        } catch (std::exception e) {
            std::cout << "unknown opcode detected: '" << opcode << "'" << std::endl;
            return {OPCODE::UNKNOWN, OPTYPE::BLOCK};
        }
    }
};