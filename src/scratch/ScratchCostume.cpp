#include "ScratchCostume.hpp"

ScratchCostume::ScratchCostume(json sc):
    ScratchAsset(sc),
    bitmapResolution(sc["bitmapResolution"]),
    rotationCenterX(sc["rotationCenterX"]),
    rotationCenterY(sc["rotationCenterY"])
{}

void ScratchCostume::load_image(std::string tempdir) {
    if (this->dataFormat == "svg") {
        std::string command = "magick convert " + tempdir + this->md5ext + " " + tempdir + this->assetId + ".png";
        std::cout << "converting " << this->md5ext << " to png" << std::endl;
        system(command.c_str());
        this->texture.loadFromFile(tempdir + this->assetId + ".png");
    } else {
        this->texture.loadFromFile(tempdir + this->md5ext);
    }
}