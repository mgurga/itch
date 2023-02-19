#include "ScratchAsset.hpp"

ScratchAsset::ScratchAsset(json sa):
    name(sa["name"]),
    dataFormat(sa["dataFormat"]),
    assetId(sa["assetId"]),
    md5ext(sa["md5ext"])
{}