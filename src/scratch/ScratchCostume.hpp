#pragma once

#include <lunasvg.h>

#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "../player/ImageResource.hpp"
#include "ScratchAsset.hpp"

using namespace lunasvg;
using json = nlohmann::json;

class ScratchCostume : public ScratchAsset {
public:
    ScratchCostume(json sc);
    void load_image(std::filesystem::path tempdir);

    ImageResource& get_image_resource() { return texture; }
    float get_rot_center_x() { return rotationCenterX; }
    float get_rot_center_y() { return rotationCenterY; }
    int get_bitmap_res() { return bitmapResolution; }

    void set_rot_center_x(float f) { rotationCenterX = f; }
    void set_rot_center_y(float f) { rotationCenterY = f; }
    void set_bitmap_res(int b) { bitmapResolution = b; }

private:
    int bitmapResolution;
    float rotationCenterX;
    float rotationCenterY;

    ImageResource texture;
};