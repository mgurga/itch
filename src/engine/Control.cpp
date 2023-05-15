#include "Engine.hpp"

void EngineFunctions::Engine::wait(double duration, Chain& c, int& i) {
    if (!c.continue_at.empty() && c.continue_at.back().end_time.has_value()) {
        if (c.continue_at.back().end_time <= std::chrono::high_resolution_clock::now()) {
            c.continue_at.pop_back();
        } else {
            i = -1;
        }
    } else {
        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = std::chrono::high_resolution_clock::now();
        rp.end_time.value() += std::chrono::milliseconds(static_cast<long>(duration * 1000));
        c.continue_at.push_back(rp);
        i = -1;
    }
}

void EngineFunctions::Engine::forever_loop(Link link, Chain& c, ScratchTarget* s, int& i) {
    if (!link.inputs_contains("SUBSTACK")) return;
    // if (link.inputs["SUBSTACK"][1].is_null()) return;
    if (!c.continue_at.empty() && !c.continue_at.back().end_time.has_value()) {
        process_chain(get_chain_by_link_id(link.inputs["SUBSTACK"][1], s), s, true);
    } else {
        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = {};
        c.continue_at.push_back(rp);
    }
}

void EngineFunctions::Engine::stop_menu(Link link, Chain& c, ScratchTarget* s, int& i) {
    std::string stopop = link.fields["STOP_OPTION"][0];

    if (stopop == "all") {
        for (ScratchSprite& ss : prj->sprites) {
            for (Chain& cc : ss.chains) {
                cc.activatable = false;
                cc.continue_at.clear();
            }
        }

        for (Chain& cc : prj->stage.chains) {
            cc.activatable = false;
            cc.continue_at.clear();
        }

        i = -1;
    } else if (stopop == "this script") {
        c.activatable = false;
        c.continue_at.clear();
        i = -1;
    } else if (stopop == "other scripts in sprite") {
        for (Chain& cc : s->chains) {
            if (cc.links.at(0).id != c.links.at(0).id) {
                cc.activatable = false;
                cc.continue_at.clear();
            }
        }
    } else {
        std::cout << "unknown stop option: " << stopop << std::endl;
    }
}

void EngineFunctions::Engine::if_statement(Link link, ScratchTarget* s) {
    if (!link.inputs_contains("CONDITION") || !link.inputs_contains("SUBSTACK")) return;
    // if (link.inputs["SUBSTACK"][1].is_null()) return;
    std::string cid = link.inputs["CONDITION"][1];
    if (compute_condition(cid, s)) {
        process_chain(get_chain_by_link_id(link.inputs["SUBSTACK"][1], s), s, true);
    }
}

void EngineFunctions::Engine::if_else_statement(Link link, ScratchTarget* s) {
    if (!link.inputs_contains("CONDITION")) {
        if (link.inputs_contains("SUBSTACK2"))
            process_chain(get_chain_by_link_id(link.inputs["SUBSTACK2"][1], s), s, true);
        return;
    }
    // if (link.inputs["SUBSTACK"][1].is_null()) return;
    // if (link.inputs["SUBSTACK2"][1].is_null()) return;
    std::string cid = link.inputs["CONDITION"][1];
    if (compute_condition(cid, s)) {
        if (!link.inputs_contains("SUBSTACK")) return;
        process_chain(get_chain_by_link_id(link.inputs["SUBSTACK"][1], s), s, true);
    } else {
        if (!link.inputs_contains("SUBSTACK2")) return;
        Chain& c = get_chain_by_link_id(link.inputs["SUBSTACK2"][1], s);
        process_chain(c, s, true);
    }
}

void EngineFunctions::Engine::repeat_loop(Link link, Chain& c, ScratchTarget* s, int& i) {
    if (!link.inputs_contains("SUBSTACK")) return;
    // if (link.inputs["SUBSTACK"][1].is_null()) return;
    double times = compute_input(link.inputs["TIMES"], s);
    if (times <= 0) return;
    if (!c.continue_at.empty() && !c.continue_at.back().end_time.has_value()) {
        if (c.continue_at.back().runs >= times) {
            c.continue_at.pop_back();
            return;
        }
        Chain& schain = get_chain_by_link_id(link.inputs["SUBSTACK"][1], s);
        if (schain.continue_at.empty()) c.continue_at.back().runs++;
        process_chain(schain, s, true);
        i = -1;
    } else {
        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = {};
        rp.runs = 0;
        c.continue_at.push_back(rp);
        i = -1;
    }
}

void EngineFunctions::Engine::create_clone_of(Link link, ScratchTarget* s) {
    std::string clone_target =
        get_link_by_id(link.inputs["CLONE_OPTION"][1]).fields["CLONE_OPTION"][0];

    if (clone_target == "_myself_") {
        ScratchSprite st_copy = *dynamic_cast<ScratchSprite*>(s);
        for (Chain& c : st_copy.chains) {
            if (c.links.at(0).opcode != OPCODE::START_AS_CLONE)
                c.activatable = false;
            else
                c.activatable = true;
            c.continue_at = {};
        }
        clones.push_back(st_copy);
    } else {
        ScratchSprite st_copy = *dynamic_cast<ScratchSprite*>(&get_target_by_name(clone_target));
        for (Chain& c : st_copy.chains) {
            if (c.links.at(0).opcode != OPCODE::START_AS_CLONE)
                c.activatable = false;
            else
                c.activatable = true;
            c.continue_at = {};
        }
        clones.push_back(st_copy);
    }
}