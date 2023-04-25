#include "Engine.hpp"

Value EngineFunctions::Engine::compute_condition(std::string opid, ScratchSprite* s) {
    Link op = get_sb_by_id(opid);

    if (op.opcode == OPCODE::KEY_PRESSED) {
        ScratchBlock ko = get_sb_by_id(op.inputs["KEY_OPTION"][1]);
        std::string key = ko.fields["KEY_OPTION"][0];
        for (std::string pkey : pi->keys_down)
            if (pkey == key) return true;
        return false;
    }

    switch (op.opcode.opcode) {
    case OPCODE::MOUSE_DOWN: return pi->mouse_down;
    case OPCODE::OPERATOR_AND:
        if (!op.inputs.contains("OPERAND1") && !op.inputs.contains("OPERAND2")) return false;
        if (!op.inputs.contains("OPERAND1") || !op.inputs.contains("OPERAND2")) return false;
        return compute_condition(op.inputs["OPERAND1"][1], s).get_bool() &&
               compute_condition(op.inputs["OPERAND2"][1], s).get_bool();
    case OPCODE::OPERATOR_OR:
        if (!op.inputs.contains("OPERAND1") && !op.inputs.contains("OPERAND2")) return false;
        if (!op.inputs.contains("OPERAND1")) return compute_condition(op.inputs["OPERAND2"][1], s);
        if (!op.inputs.contains("OPERAND2")) return compute_condition(op.inputs["OPERAND1"][1], s);
        return compute_condition(op.inputs["OPERAND1"][1], s).get_bool() ||
               compute_condition(op.inputs["OPERAND2"][1], s).get_bool();
    case OPCODE::OPERATOR_NOT:
        if (!op.inputs.contains("OPERAND")) return true;
        return !compute_condition(op.inputs["OPERAND"][1], s).get_bool();
    case OPCODE::OPERATOR_LESS_THAN:
        return compute_input(op.inputs["OPERAND1"], s).get_number() <
               compute_input(op.inputs["OPERAND2"], s).get_number();
    case OPCODE::OPERATOR_GREATER_THAN:
        return compute_input(op.inputs["OPERAND1"], s).get_number() >
               compute_input(op.inputs["OPERAND2"], s).get_number();
    case OPCODE::OPERATOR_EQUALS:
        return compute_input(op.inputs["OPERAND1"], s).get_number() ==
               compute_input(op.inputs["OPERAND2"], s).get_number();
    default: break;
    }

    std::cout << "unknown condition: '" << op.string_opcode << "' returning false" << std::endl;
    return false;
}