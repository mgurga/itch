#include "ScratchSound.hpp"

ScratchSound::ScratchSound(json ss):
    ScratchAsset(ss),
    rate(ss["rate"]),
    sampleCount(ss["sampleCount"])
{}

void ScratchSound::load_sound(std::filesystem::path tempdir) {
    if (!this->sound.loadFromFile((tempdir / this->md5ext).string()))
        std::cout << "could not load sound file: " << this->md5ext << std::endl;
}
