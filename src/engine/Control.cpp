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
        rp.end_time.value() += std::chrono::seconds(static_cast<long>(duration));
        c.continue_at.push_back(rp);
        i = -1;
    }
}

void EngineFunctions::Engine::forever_loop(Link link, Chain& c, ScratchSprite* s, int& i) {
    if (!link.inputs.contains("SUBSTACK"))
        return;
    if (!c.continue_at.empty() && !c.continue_at.back().end_time.has_value()) {
        auto get_chain = [&] (std::string id)-> Chain& {
            for (Chain& gc : s->chains)
                if (gc.links.at(0).block_id == id)
                    return gc;
            throw std::invalid_argument("chain with beginning link id '" + id + "' not found");
        };

        process_chain(get_chain(link.inputs["SUBSTACK"][1]), s, true);
    } else {
        ResumePoint rp;
        rp.link_num = i;
        rp.start_time = std::chrono::high_resolution_clock::now();
        rp.end_time = {};
        c.continue_at.push_back(rp);
    }
}

void EngineFunctions::Engine::stop_menu(Link link, Chain& c, ScratchSprite* s, int& i) {
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
            if (cc.links.at(0).block_id != c.links.at(0).block_id) {
                cc.activatable = false;
                cc.continue_at.clear();
            }
        }
    } else {
        std::cout << "unknown stop option: " << stopop << std::endl;
    }
}

void EngineFunctions::Engine::if_statement(Link link, Chain& c, ScratchSprite* s) {
    if (!link.inputs.contains("CONDITION") || !link.inputs.contains("SUBSTACK"))
        return;
    std::string cid = link.inputs["CONDITION"][1];
    if (compute_condition(cid)) {
        auto get_chain = [&] (std::string id)-> Chain& {
            for (Chain& gc : s->chains)
                if (gc.links.at(0).block_id == id)
                    return gc;
            throw std::invalid_argument("chain with beginning link id '" + id + "' not found");
        };

        std::cout << "processing chain" << std::endl;
        process_chain(get_chain(link.inputs["SUBSTACK"][1]), s, true);
    }
}