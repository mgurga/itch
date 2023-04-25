#include "Engine.hpp"

Value EngineFunctions::Engine::compute_reporter(std::string opid, ScratchSprite* s) {
    Link op = get_reporter_by_id(opid);

    if (op.opcode == OPTYPE::CONDITIONAL) return compute_condition(opid, s);

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
        std::uniform_int_distribution<int> r(compute_input(op.inputs["FROM"], s).get_number(),
                                             compute_input(op.inputs["TO"], s).get_number());
        return static_cast<double>(r(rng));
    }

    switch (op.opcode.opcode) {
    case OPCODE::COSTUME_NUM_NAME:
        if (op.fields["NUMBER_NAME"][0].get<std::string>() == "number") {
            return s->currentCostume;
        } else {
            return s->costumes[s->currentCostume].name;
        }
    case OPCODE::OPERATOR_JOIN:
        return compute_input(op.inputs["STRING1"], s).get_string() +
               compute_input(op.inputs["STRING2"], s).get_string();
    case OPCODE::LIST_LENGTH:
        return get_list_by_name(op.fields["LIST"][0].get<std::string>()).length();
    case OPCODE::LIST_ITEM:
        return get_list_by_name(op.fields["LIST"][0].get<std::string>())
            .at(compute_input(op.inputs["INDEX"], s).get_number());
    case OPCODE::MOUSE_X: return pi->mouse_x;
    case OPCODE::MOUSE_Y: return pi->mouse_y;
    case OPCODE::X_POS: return s->x;
    case OPCODE::Y_POS: return s->y;
    case OPCODE::DIRECTION: return s->direction;
    case OPCODE::SIZE_VAL: return s->size;
    case OPCODE::LOUDNESS: return -1;
    default:
        std::cout << "unknown reporter: '" + op.string_opcode + "'" << std::endl;
        return Value("");
    }
}