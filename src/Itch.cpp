#include "Itch.hpp"
#include "FileHandler.hpp"

Itch::Itch(std::string sb3_file) {
    // cleanup old files
    std::cout << "cleaning up old files" << std::endl;
    std::filesystem::remove_all(temp_dir);

    std::cout << "got sb3 file: " << sb3_file << std::endl;

    FileHandler sb3 = FileHandler(sb3_file, *this);
    sb3.init([&] () {
        std::cout << "finished unzipping sb3" << std::endl;

        project = Project(temp_dir + "project.json");
        project.load_from_project_json();
    });
}

void Itch::draw() {

}