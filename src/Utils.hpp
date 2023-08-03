
#include <algorithm>
#include <string>
#include <vector>

class Utils {
public:
    static bool contains(const std::vector<std::string>& vec, const std::string& item) {
        return (std::find(vec.begin(), vec.end(), item) != vec.end());
    }
};