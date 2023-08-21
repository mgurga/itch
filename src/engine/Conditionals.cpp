#include "Engine.hpp"

Value EngineFunctions::Engine::compute_condition(Link op, ScratchTarget* s) {
    if (op.opcode == OPCODE::KEY_PRESSED) {
        Link& ko = get_link_by_id(op.inputs["KEY_OPTION"][1]);
        std::string key = ko.fields["KEY_OPTION"][0];
        for (std::string pkey : pi->keys_down)
            if (pkey == key) return true;
        return false;
    }

    switch (op.opcode.opcode) {
    case OPCODE::MOUSE_DOWN: return pi->mouse_down;
    case OPCODE::OPERATOR_AND:
        if (!op.inputs_contains("OPERAND1") && !op.inputs_contains("OPERAND2")) return false;
        if (!op.inputs_contains("OPERAND1") || !op.inputs_contains("OPERAND2")) return false;
        return compute_condition(get_link_by_id(op.inputs["OPERAND1"][1]), s).get_bool() &&
               compute_condition(get_link_by_id(op.inputs["OPERAND2"][1]), s).get_bool();
    case OPCODE::OPERATOR_OR:
        if (!op.inputs_contains("OPERAND1") && !op.inputs_contains("OPERAND2")) return false;
        if (!op.inputs_contains("OPERAND1"))
            return compute_condition(get_link_by_id(op.inputs["OPERAND2"][1]), s);
        if (!op.inputs_contains("OPERAND2"))
            return compute_condition(get_link_by_id(op.inputs["OPERAND1"][1]), s);
        return compute_condition(get_link_by_id(op.inputs["OPERAND1"][1]), s).get_bool() ||
               compute_condition(get_link_by_id(op.inputs["OPERAND2"][1]), s).get_bool();
    case OPCODE::OPERATOR_NOT:
        if (!op.inputs_contains("OPERAND")) return true;
        return !compute_condition(get_link_by_id(op.inputs["OPERAND"][1]), s).get_bool();
    case OPCODE::OPERATOR_LESS_THAN:
        return compute_input(op.inputs["OPERAND1"], s).get_number() <
               compute_input(op.inputs["OPERAND2"], s).get_number();
    case OPCODE::OPERATOR_GREATER_THAN:
        return compute_input(op.inputs["OPERAND1"], s).get_number() >
               compute_input(op.inputs["OPERAND2"], s).get_number();
    case OPCODE::OPERATOR_EQUALS:
        return compute_input(op.inputs["OPERAND1"], s).get_variant() ==
               compute_input(op.inputs["OPERAND2"], s).get_variant();
    case OPCODE::LIST_CONTAINS:
        return get_list_by_name(op.fields["LIST"][0]).contains(compute_input(op.inputs["ITEM"], s));
    case OPCODE::ARG_BOOLEAN: return get_proc_var_by_name(op.fields["VALUE"][0]).val().get_bool();
    default: break;
    }

    std::cout << "unknown condition: '" << op.string_opcode << "' returning false" << std::endl;
    return false;
}