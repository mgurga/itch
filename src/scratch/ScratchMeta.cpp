#include "ScratchMeta.hpp"

ScratchMeta::ScratchMeta() {}
ScratchMeta::ScratchMeta(json sm): semver(sm["semver"]), vm(sm["vm"]), agent(sm["agent"]) {}