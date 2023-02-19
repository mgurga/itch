#include "ScratchTarget.hpp"

ScratchTarget::ScratchTarget(json st, std::string temp_dir):
    isStage(st["isStage"]),
    name(st["name"]),
    volume(st["volume"]),
    layerOrder(st["layerOrder"]),
    currentCostume(st["currentCostume"])
{
    std::cout << "loading variables..." << std::endl;
    for (auto sv : st["variables"]) {
        variables.push_back(ScratchVariable(sv));
    }

    std::cout << "loading costumes..." << std::endl;
    for (auto sc : st["costumes"]) {
        costumes.push_back(ScratchCostume(sc));
        costumes.back().load_image(temp_dir);
    }

    std::cout << "loading sounds..." << std::endl;
    for (auto ss : st["sounds"]) {
        sounds.push_back(ScratchSound(ss));
        sounds.back().load_sound(temp_dir);
    }
}