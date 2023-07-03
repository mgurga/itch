#include "Engine.hpp"

void EngineFunctions::Engine::call_procedure(Link link, ScratchTarget* s) {
    auto get_chain_from_proccode = [&](std::string proccode) -> Chain& {
        for (Chain& c : s->chains) {
            if (c.links.at(0).opcode == OPCODE::DEFINITION) {
                if (get_link_by_id(c.links.at(0).inputs["custom_block"][1])
                        .mutations["proccode"][0] == proccode)
                    return c;
            }
        }
        throw std::invalid_argument("definition with proccode '" + proccode + "' not found.");
    };

    Chain& proc_definition = get_chain_from_proccode(link.mutations["proccode"][0]);
    Link& proc_prototype = get_link_by_id(proc_definition.links.at(0).inputs["custom_block"][1]);

    // check if definition contains anything that cannot be processed immediately
    bool pauses_flow = false;
    for (const Link& l : proc_definition.links)
        if (l.opcode.opcode == OPCODE::WAIT || l.opcode.opcode == OPCODE::WAIT_UNTIL ||
            l.opcode.opcode == OPCODE::SAY_FOR_SECS ||
            l.opcode.opcode == OPCODE::BROADCAST_AND_WAIT)
            pauses_flow = true;

    // add procedure call inputs as variables
    for (auto in : link.inputs) {
        // find argument name from prototype mutation
        std::string var_name;
        for (int i = 0; i < proc_prototype.mutations["argumentids"].size(); i++) {
            if (in.first == proc_prototype.mutations["argumentids"][i]) {
                var_name = proc_prototype.mutations["argumentnames"][i];
                break;
            }
        }

        // std::cout << var_name << " evaluates to " << compute_input(in.second, s).debug_string()
        //   << std::endl;

        procedure_variables.push_back(Variable(var_name, compute_input(in.second, s), in.first));
    }

    if (link.mutations["warp"][0] == "true" && !pauses_flow) {
        int start_link = 1;  // skip the definition block by starting at the next link

        for (int i = start_link; i < proc_definition.links.size(); i++) {
            int pre_process = i;
            process_link(proc_definition.links.at(i), proc_definition, s, i);
            if (i == -1) {
                std::cout << "link in warp procedure tried changing control flow. link opcode: "
                          << proc_definition.links.at(i).string_opcode << ". skipping..."
                          << std::endl;
                i = pre_process;
            }
        }
    } else {
        process_chain(proc_definition, s, true);
    }

    // delete procedure call inputs from procecdure_variables list
    for (std::string an : proc_prototype.mutations["argumentnames"]) {
        procedure_variables.erase(
            std::remove_if(procedure_variables.begin(), procedure_variables.end(),
                           [&](Variable v) { return v.name == an; }),
            procedure_variables.end());
    }
}