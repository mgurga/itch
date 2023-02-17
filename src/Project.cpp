#include "Project.hpp"

Project::Project(): project_file_name("") {}
Project::Project(std::string pjf): project_file_name(pjf) {}

void Project::load_from_project_json() {
    std::ifstream f(project_file_name);
    project_json = json::parse(f);
}