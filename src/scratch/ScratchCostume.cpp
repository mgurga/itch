#include "ScratchCostume.hpp"

ScratchCostume::ScratchCostume(json sc):
    ScratchAsset(sc),
    rotationCenterX(sc["rotationCenterX"]),
    rotationCenterY(sc["rotationCenterY"])
{
    bitmapResolution = sc.contains("bitmapResolution") ? int(sc["bitmapResolution"]) : -1;
}

void ScratchCostume::load_image(std::filesystem::path tempdir) {
    if (this->dataFormat == "svg") {
        std::filesystem::path newfile = tempdir / (this->assetId + ".png");
        std::string command = "magick convert -background none " + (tempdir / this->md5ext).string() + " " + newfile.string();
        std::cout << "converting " << this->md5ext << " to png" << std::endl;
        system(command.c_str());
        this->texture.loadFromFile(newfile.string());
    } else {
        this->texture.loadFromFile((tempdir / this->md5ext).string());
    }
}