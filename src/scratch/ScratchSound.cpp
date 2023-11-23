#include "ScratchSound.hpp"

ScratchSound::ScratchSound(json ss) :
    ScratchAsset(ss), rate(ss["rate"]), sampleCount(ss["sampleCount"]) {}

void ScratchSound::load_sound(std::filesystem::path tempdir) {
    sound.load_from_file(tempdir / this->md5ext);
}
