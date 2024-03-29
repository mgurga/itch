#include "Project.hpp"

Project::Project(): temp_dir("") {}
Project::Project(std::filesystem::path pjf): temp_dir(pjf) {}

void Project::load_from_project_json(bool heavyload) {
    std::ifstream f(temp_dir / "project.json");
    project_json = json::parse(f);

    if (project_json.contains("info")) {
        std::cout << "project is built for Scratch 2.0 and that is not currently supported. quitting..." << std::endl;
        exit(1);
    }

    for (auto target : project_json["targets"]) {
        std::cout << "loading target: " << target["name"] << std::endl;
        if (target["isStage"]) {
            this->stage = ScratchStage(target, temp_dir, heavyload);
        } else {
            this->sprites.push_back(ScratchSprite(target, temp_dir, heavyload));
        }
    }

    std::cout << "loading monitors..." << std::endl;
    for (auto sm : project_json["monitors"]) {
        monitors.push_back(ScratchMonitor(sm));
    }

    this->meta = ScratchMeta(project_json["meta"]);

    std::cout << "finished loading project" << std::endl;
}