#include "ScratchSound.hpp"

ScratchSound::ScratchSound(json ss):
    ScratchAsset(ss),
    rate(ss["rate"]),
    sampleCount(ss["sampleCount"])
{}

void ScratchSound::load_sound(std::string tempdir) {
    if (!this->sound.loadFromFile(tempdir + this->md5ext))
        std::cout << "could not load sound file: " << this->md5ext << std::endl;
}
