#include "Project.hpp"

Project::Project(): temp_dir("") {}
Project::Project(std::string pjf): temp_dir(pjf) {}

void Project::load_from_project_json() {
    std::ifstream f(temp_dir + "project.json");
    project_json = json::parse(f);

    for (auto target : project_json["targets"]) {
        std::cout << "loading target: " << target["name"] << std::endl;
        this->targets.push_back(ScratchTarget(target, temp_dir));
    }

    std::cout << "loading monitors..." << std::endl;
    for (auto sm : project_json["monitors"]) {
        monitors.push_back(ScratchMonitor(sm));
    }

    this->meta = ScratchMeta(project_json["meta"]);

    std::cout << "finished loading project" << std::endl;
}