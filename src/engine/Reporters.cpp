#include "Engine.hpp"

// always pass a scratch target when possible.
// only pass a nullptr when you know 100% the target is not used.
// for example:
// sensing_timer - does not need a target
// motion_xposition - needs a target
Value EngineFunctions::Engine::compute_reporter(Link op, ScratchTarget* s) {
    if (op.opcode == OPTYPE::CONDITIONAL) return compute_condition(op, s);

    // basic math operations: add, subtract, multiple, divide, modulo
    if ((op.opcode.opcode >= 400 && op.opcode.opcode <= 403) ||
        op.opcode.opcode == OPCODE::OPERATOR_MOD) {
        Value num1, num2;
        num1 = compute_input(op.inputs["NUM1"], s);
        num2 = compute_input(op.inputs["NUM2"], s);

        if (num1.contains_number() && num2.contains_number()) {
            switch (op.opcode.opcode) {
            case OPERATOR_ADD: return num1.get_number() + num2.get_number();
            case OPERATOR_SUBTRACT: return num1.get_number() - num2.get_number();
            case OPERATOR_MULTIPLY: return num1.get_number() * num2.get_number();
            case OPERATOR_DIVIDE: return num1.get_number() / num2.get_number();
            case OPERATOR_MOD: return std::fmod(num1.get_number(), num2.get_number());
            default: break;
            }
        } else if (num1.contains_number()) {
            return num1.get_number();
        } else if (num2.contains_number()) {
            return num2.get_number();
        }
    }

    if (op.opcode == OPCODE::OPERATOR_RANDOM) {
        std::random_device dev;
        std::mt19937 rng(dev());
        int from = static_cast<int>(compute_input(op.inputs["FROM"], s).get_number());
        int to = static_cast<int>(compute_input(op.inputs["TO"], s).get_number());
        std::uniform_int_distribution<int> r(from, to);
        return static_cast<double>(r(rng));
    }

    if (op.opcode.opcode == OPCODE::OF) {
        std::string prop = op.fields["PROPERTY"][0];
        Link& ofmenu = get_link_by_id(op.inputs["OBJECT"][1]);
        std::string target = ofmenu.fields["OBJECT"][0];

        if (target == "_stage_") {
            if (prop == "backdrop #") return prj->stage.get_current_costume() + 1;
            if (prop == "backdrop name") return prj->stage.costume().name;
            if (prop == "volume") return prj->stage.get_volume();

            return get_var_by_name(prop).val();
        } else {
            try {
                ScratchTarget& t = get_target_by_name(target);
                if (prop == "x position") return t.get_x();
                if (prop == "y position") return t.get_y();
                if (prop == "direction") return t.get_direction();
                if (prop == "costume #") return t.get_current_costume() + 1;
                if (prop == "costume name") return t.costume().name;
                if (prop == "size") return t.get_size();
                if (prop == "volume") return t.get_volume();
            } catch (std::invalid_argument e) { return Value(""); }
        }
    }

    if (op.opcode.opcode == OPCODE::CURRENT_TIME) {
        std::string period = op.fields["CURRENTMENU"][0];
        auto curtime = std::chrono::system_clock::now();
        time_t t = std::chrono::system_clock::to_time_t(curtime);
        auto tm = localtime(&t);

        if (period == "DATE") return tm->tm_mday;
        if (period == "YEAR") return 1900 + tm->tm_year;
        if (period == "MONTH") return tm->tm_mon + 1;
        if (period == "DAYOFWEEK") return tm->tm_wday + 1;
        if (period == "HOUR") return tm->tm_hour;
        if (period == "MINUTE") return tm->tm_min;
        if (period == "SECOND") return tm->tm_sec;
    }

    if (op.opcode.opcode == OPCODE::OPERATOR_MATHOP) {
        std::string mathop = op.fields["OPERATOR"][0];
        Value in = compute_input(op.inputs["NUM"], s);

        if (mathop == "abs") return std::abs(in.get_number());
        if (mathop == "floor") return std::floor(in.get_number());
        if (mathop == "ceiling") return std::ceil(in.get_number());
        if (mathop == "sqrt") return std::sqrt(in.get_number());
        if (mathop == "sin") return std::sin(in.get_number() * PI / 180);
        if (mathop == "cos") return std::cos(in.get_number() * PI / 180);
        if (mathop == "tan") return std::tan(in.get_number() * PI / 180);
        if (mathop == "asin") return std::asin(in.get_number()) * 180 / PI;
        if (mathop == "acos") return std::acos(in.get_number()) * 180 / PI;
        if (mathop == "atan") return std::atan(in.get_number()) * 180 / PI;
        if (mathop == "ln") return std::log(in.get_number());
        if (mathop == "log") return std::log10(in.get_number());
        if (mathop == "e ^") return std::exp(in.get_number());
        if (mathop == "10 ^") return std::pow(in.get_number(), 10);

        std::cout << "unknown mathop operation: " << mathop << " returning 0" << std::endl;
        return Value(0);
    }

    switch (op.opcode.opcode) {
    case OPCODE::COSTUME: return op.fields["COSTUME"][0];
    case OPCODE::COSTUME_NUM_NAME:
        if (op.fields["NUMBER_NAME"][0] == "number") {
            return s->get_current_costume() + 1;
        } else {
            return s->costume().name;
        }
    case OPCODE::OPERATOR_JOIN:
        return compute_input(op.inputs["STRING1"], s).get_string() +
               compute_input(op.inputs["STRING2"], s).get_string();
    case OPCODE::LIST_LENGTH: return get_list_by_name(op.fields["LIST"][0]).length();
    case OPCODE::LIST_ITEM:
        return get_list_by_name(op.fields["LIST"][0])[static_cast<int>(
            compute_input(op.inputs["INDEX"], s).get_number())];
    case OPCODE::MOUSE_X: return pi->mouse_x;
    case OPCODE::MOUSE_Y: return pi->mouse_y;
    case OPCODE::X_POS: return s->get_x();
    case OPCODE::Y_POS: return s->get_y();
    case OPCODE::DIRECTION: return s->get_direction();
    case OPCODE::SIZE_VAL: return s->get_size();
    case OPCODE::LOUDNESS: return -1;
    case OPCODE::TIMER: return get_timer_progress();
    case OPCODE::BACKDROP_NUM_NAME:
        if (op.fields["NUMBER_NAME"][0] == "number") {
            return prj->stage.get_current_costume() + 1;
        } else {
            return prj->stage.costume().name;
        }
    case OPCODE::USERNAME: return Value();  // empty string
    case OPCODE::VOLUME: return s->get_volume();
    case OPCODE::ANSWER: return Value();
    case OPCODE::ARG_STRING_NUM: return get_proc_var_by_name(op.fields["VALUE"][0]).val();
    case OPCODE::OPERATOR_LENGTH: return compute_input(op.inputs["STRING1"], s).get_string().size();
    case OPCODE::OPERATOR_LETTER_OF:
        try {
            return compute_input(op.inputs["STRING"], s)
                .get_string()
                .at(compute_input(op.inputs["LETTER"], s).get_number() - 1);
        } catch (std::out_of_range const& e) { return Value(); }
    default:
        std::cout << "unknown reporter: '" + op.string_opcode + "'" << std::endl;
        return Value();  // empty string
    }
}