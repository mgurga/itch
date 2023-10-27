#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using json = nlohmann::json;

enum class BlockType {
    Uninitialized = 0,
    Number = 4,
    Positive_Number = 5,
    Positive_Integer = 6,
    Integer = 7,
    Angle = 8,
    Color = 9,
    String = 10,
    Broadcast = 11,
    VariableType = 12,
    ListType = 13
};

class ScratchArrayBlock {
public:
    ScratchArrayBlock() { type = BlockType::Uninitialized; }
    ScratchArrayBlock(json sb, std::string id = "") {
        type = static_cast<BlockType>(sb[0]);
        block_id = id;

        switch (type) {
        case BlockType::Number:
        case BlockType::Positive_Integer:
        case BlockType::Positive_Number:
        case BlockType::Integer:
        case BlockType::Angle:
            if (!(sb[1].get<std::string>() == "")) num_val = std::stod(sb[1].get<std::string>());
            break;
        case BlockType::Color:
        case BlockType::String: str_value = sb[1]; break;
        case BlockType::Broadcast:
            str_value = sb[1];
            element_id = sb[2];
            break;
        case BlockType::VariableType:
        case BlockType::ListType:
            str_value = sb[1];
            element_id = sb[2];
            // reporters do not have x and y variables
            if (sb.size() >= 4) {
                x = sb[3];
                y = sb[4];
            }
            break;
        default: break;
        }
    }

    std::optional<std::string> get_block_id() {
        if (block_id.empty()) {
            return {};
        } else {
            return block_id;
        }
    }

    BlockType type;
    double num_val = 0;
    std::string str_value = "";
    std::string element_id;
    int x, y;

private:
    std::string block_id;
};
