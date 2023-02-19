#include "ScratchTarget.hpp"

ScratchTarget::ScratchTarget(json st):
    isStage(st["isStage"]),
    name(st["name"]),
    volume(st["volume"]),
    layerOrder(st["layerOrder"])
{
    for (auto sv : st["variables"]) {
        variables.push_back(ScratchVariable(sv));
    }
}