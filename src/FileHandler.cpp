#include "FileHandler.hpp"

FileHandler::FileHandler(std::string fn, std::string temp_dir): file_name(fn), temp_dir(temp_dir), file_name_no_ext(fn.substr(0, fn.find_last_of("."))) {}

void FileHandler::init(std::function<void()> callback) {
    std::cout << "initalizing sb3 file" << std::endl;

    int szout = system(std::string("7z x " + file_name + " -o" + temp_dir).c_str());

    initialized = true;
    callback();
}