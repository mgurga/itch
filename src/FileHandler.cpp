#include "FileHandler.hpp"

FileHandler::FileHandler(std::filesystem::path fn, std::filesystem::path temp_dir):
    file_name(fn),
    temp_dir(temp_dir),
    file_name_no_ext(fn.string().substr(0, fn.string().find_last_of(".")))
{}

void FileHandler::init(std::function<void()> callback) {
    std::cout << "initalizing sb3 file" << std::endl;

    int szout = system(std::string("7z x " + file_name.string() + " -o" + temp_dir.string()).c_str());

    initialized = true;
    callback();
}