
#include <algorithm>
#include <string>
#include <vector>

class Utils {
public:
    static bool contains(const std::vector<std::string>& vec, const std::string& item) {
        return (std::find(vec.begin(), vec.end(), item) != vec.end());
    }

    static std::string to_scratch_key(int in) {
        if (in >= 48 && in <= 90) { return std::string(char(in), 0); }
        switch (in) {
        case 32: return "space";
        case 37: return "left arrow";
        case 39: return "right arrow";
        case 38: return "up arrow";
        case 40: return "down arrow";
        default: return "";
        }
    }
};