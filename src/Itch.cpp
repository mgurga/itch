#include "Itch.hpp"

Itch::Itch(ItchOptions& io) : options(io) {}

void Itch::init() {
    if (!options.headless) player = new Player(options.running);
    // std::cout << "cleaning up old files" << std::endl;
    // if (std::filesystem::exists(temp_dir)) std::filesystem::remove_all(temp_dir);
    if (!std::filesystem::exists(options.tempdir))
        std::filesystem::create_directory(options.tempdir);
    if (options.debugwindow) {
        debug_window = new DebugWindow(&engine, &project, pause_engine, options.running);
        pause_engine = true;
    }
    std::cout << "initialized itch" << std::endl;
}

void Itch::load_from_folder(std::filesystem::path sb3_folder) {
    if (!std::filesystem::is_directory(sb3_folder)) {
        std::cout << sb3_folder << " is not a directory" << std::endl;
        exit(1);
    }

    if (!std::filesystem::exists(sb3_folder / "project.json")) {
        std::cout << sb3_folder << " does not contain a project.json" << std::endl;
        exit(1);
    }

    project = Project(sb3_folder);
    project.load_from_project_json();

    engine = EngineFunctions::Engine(options, project);
}

void Itch::load_from_file(std::filesystem::path sb3_file) {
    if (std::filesystem::exists(options.tempdir)) {
        std::filesystem::remove_all(options.tempdir);
        std::filesystem::create_directory(options.tempdir);
    }
    std::cout << "got sb3 file: " << sb3_file << std::endl;

    FileHandler sb3 = FileHandler(sb3_file, options.tempdir);
    sb3.init([&]() {
        std::cout << "finished unzipping sb3" << std::endl;

        project = Project(options.tempdir);
        project.load_from_project_json();

        engine = EngineFunctions::Engine(options, project);
    });
}

void Itch::load_from_url(std::string project_url) {
#if BUILD_NETWORK_SUPPORT
    if (std::filesystem::exists(options.tempdir)) {
        std::filesystem::remove_all(options.tempdir);
        std::filesystem::create_directory(options.tempdir);
    }

    std::stringstream urlss(project_url);
    std::string seg;
    std::vector<std::string> url_parts;

    while (std::getline(urlss, seg, '/')) { url_parts.push_back(seg); }

    if (url_parts.back() == "editor") url_parts.pop_back();

    std::string pid = url_parts.back();
    std::cout << "project id is " << pid << std::endl;

    // get project description to get token
    cpr::Response pd_res = cpr::Get(cpr::Url{"https://api.scratch.mit.edu/projects/" + pid});
    std::cout << "response code is " << pd_res.status_code << std::endl;
    json project_description = json::parse(pd_res.text);
    std::cout << "project token is " << project_description["project_token"] << std::endl;
    std::ofstream pjdf(options.tempdir / "project_description.json");
    pjdf << pd_res.text;
    pjdf.close();

    // download project.json
    std::cout << "downloading project.json..." << std::endl;
    cpr::Response pj_res =
        cpr::Get(cpr::Url{"https://projects.scratch.mit.edu/" + pid +
                          "?token=" + project_description["project_token"].get<std::string>()});
    std::cout << "project json response code: " << pj_res.status_code << std::endl;
    json project_json = json::parse(pj_res.text);
    std::ofstream pjf;
    pjf.open(options.tempdir / "project.json");
    pjf << pj_res.text;
    pjf.close();

    // download project assets
    const std::string scratch_asset_endpoint = "https://assets.scratch.mit.edu/internalapi/asset/";
    for (json target : project_json["targets"]) {
        std::cout << "getting assets from target: " << target["name"] << std::endl;

        // costumes
        for (json cos : target["costumes"]) {
            cpr::Response c_res = cpr::Get(
                cpr::Url{scratch_asset_endpoint + cos["md5ext"].get<std::string>() + "/get/"});
            std::ofstream cf;
            cf.open(options.tempdir / cos["md5ext"].get<std::string>());
            cf << c_res.text;
            cf.close();
        }

        // sounds
        for (json snd : target["sounds"]) {
            cpr::Response s_res = cpr::Get(
                cpr::Url{scratch_asset_endpoint + snd["md5ext"].get<std::string>() + "/get/"});
            std::ofstream sf;
            sf.open(options.tempdir / snd["md5ext"].get<std::string>());
            sf << s_res.text;
            sf.close();
        }
    }

    project = Project(options.tempdir);
    project.load_from_project_json();

    engine = EngineFunctions::Engine(options, project);

#else
    std::cout << "itch was not built with network support. quitting..." << std::endl;
    exit(1);
#endif
}

void Itch::draw() {
    if (options.headless) {
        EMPTY_PLAYER_INFO(pi)
        engine.tick(&pi);

        if (engine.finished) options.running = false;
    } else {
        if (options.debugwindow) debug_window->draw();
        PlayerInfo pi = player->get_player_info();
        std::vector<std::unique_ptr<DrawOrder>> draw_orders = {};
        if (!pause_engine) {
            draw_orders = engine.tick(&pi);
        } else {
            draw_orders = engine.create_draw_order_list();
        }
        pi.pressed.clear();
        player->draw();
        player->paint(draw_orders);
    }
}