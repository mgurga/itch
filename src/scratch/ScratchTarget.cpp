#include "ScratchTarget.hpp"

ScratchTarget::ScratchTarget() {}
ScratchTarget::ScratchTarget(json st, std::filesystem::path temp_dir, bool heavyload) :
    m_isStage(st["isStage"]),
    m_name(st["name"]),
    m_volume(st["volume"]),
    m_layerOrder(st["layerOrder"]),
    m_currentCostume(st["currentCostume"]) {
    std::cout << "loading variables..." << std::endl;
    for (auto sv : st["variables"].items()) {
        variables.push_back(ScratchVariable(sv.value(), sv.key()));
    }

    std::cout << "loading lists..." << std::endl;
    for (auto sl : st["lists"].items()) { lists.push_back(ScratchList(sl.value(), sl.key())); }

    std::cout << "loading costumes..." << std::endl;
    for (auto sc : st["costumes"]) {
        costumes.push_back(ScratchCostume(sc));
        if (heavyload) costumes.back().load_image(temp_dir);
    }

    std::cout << "loading sounds..." << std::endl;
    for (auto ss : st["sounds"]) {
        sounds.push_back(ScratchSound(ss));
        if (heavyload) sounds.back().load_sound(temp_dir);
    }

    std::cout << "loading blocks..." << std::endl;
    for (auto sb : st["blocks"].items()) blocks.push_back(ScratchBlock(sb.value(), sb.key()));

    std::cout << "loading block links..." << std::endl;
    for (auto sb : blocks) links.push_back(sb);

    std::cout << "creating chains..." << std::endl;
    chains = Chain::create_chains(blocks);

    std::cout << "finished loading target: " << m_name << std::endl;
}