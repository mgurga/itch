#include "Itch.hpp"

Itch::Itch(std::filesystem::path sb3_file):
    player(Player(running))
{
    std::cout << "initalized itch" << std::endl;
    // cleanup old files
    std::cout << "cleaning up old files" << std::endl;
    if (std::filesystem::exists(temp_dir))
        std::filesystem::remove_all(temp_dir);
    std::filesystem::create_directory(temp_dir);

    std::cout << "got sb3 file: " << sb3_file << std::endl;

    FileHandler sb3 = FileHandler(sb3_file, temp_dir);
    sb3.init([&] () {
        std::cout << "finished unzipping sb3" << std::endl;

        project = Project(temp_dir);
        project.load_from_project_json();

        engine = EngineFunctions::Engine(project);
    });
}

void Itch::draw() {
    // if (player.pressed.size() != 0) {
    //     std::cout << "engine tick got pressed keys: ";
    //     for (std::string s : player.pressed) {
    //         std::cout << s << ", ";
    //     }
    //     std::cout << std::endl;
    // }

    engine.tick(project, player.pressed);
    player.pressed.clear();
    player.draw();
    player.paint(project);
}