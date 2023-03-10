
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../scratch/ScratchVariable.hpp"

using json = nlohmann::json;

class Variable {
public:
    Variable(std::string name, std::string value, std::string id = ""):
        name(name), value(value), id(id), is_global(true), is_cloud(false)
    {};
    Variable(json sv, std::string id = ""):
        name(to_string(sv[0])),
        value(to_string(sv[1])),
        is_cloud(sv.size() == 3),
        is_global(true),
        id(id)
    {};
    Variable(ScratchVariable sv):
        name(sv.name), value(sv.value), is_cloud(sv.isCloud), is_global(true), id(sv.id)
    {};

    std::string name, value;
    bool is_cloud;
    bool is_global; // otherwise only available in target
    std::string sprite_name; // if is_global is false this is sent to the sprite name

    void make_local(std::string sprite_name) {
        is_global = false;
        this->sprite_name = sprite_name;
    }

    std::optional<std::string> get_id() {
        if (id == "") {
            return {};
        } else {
            return id;
        }
    }

private:
    std::string id;
};