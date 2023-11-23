#include "ScratchCostume.hpp"

ScratchCostume::ScratchCostume(json sc) :
    ScratchAsset(sc),
    rotationCenterX(sc["rotationCenterX"]),
    rotationCenterY(sc["rotationCenterY"]) {
    bitmapResolution = sc.contains("bitmapResolution") ? int(sc["bitmapResolution"]) : 1;
}

void ScratchCostume::load_image(std::filesystem::path tempdir) {
    if (this->dataFormat == "svg") {
        std::cout << "converting " << this->md5ext << " to png" << std::endl;

        auto doc = Document::loadFromFile((tempdir / this->md5ext).string());
        if (!doc) {
            std::cout << "error loading file: " << (tempdir / this->md5ext) << std::endl;
            return;
        }

        auto bitmap = doc->renderToBitmap(0, 0, 0x00000000);
        if (!bitmap.valid()) {
            std::cout << "invalid bitmap created: " << (tempdir / this->md5ext) << std::endl;
            return;
        }
        bitmap.convertToRGBA();

        this->texture.load_from_rgba_data(bitmap.data(), bitmap.width(), bitmap.height());
    } else {
        this->texture.load_from_file(tempdir / this->md5ext);
    }
}