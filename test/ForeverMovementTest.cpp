#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"
#include "../src/engine/Engine.hpp"

class ForeverMovementTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("forevermovementtest/");
        FileHandler sb3 = FileHandler("forevermovement.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);

        engine = new EngineFunctions::Engine(*project);

        EMPTY_PLAYER_INFO(pi);
        engine->tick(&pi);
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
        delete engine;
    }

    static ScratchMonitor& get_monitor_by_name(std::string name) {
        for (ScratchMonitor& m : project->monitors)
            if (m.display_name == name) return m;
        throw std::invalid_argument("monitor with name '" + name + "' does not exist");
    }
};

Project* ForeverMovementTest::project = nullptr;
std::string* ForeverMovementTest::temp_dir = nullptr;
EngineFunctions::Engine* ForeverMovementTest::engine = nullptr;

TEST_F(ForeverMovementTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(ForeverMovementTest, InitialPositionTest) {
    ASSERT_EQ(project->sprites.at(0).get_x(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 0);
}

TEST_F(ForeverMovementTest, UpArrowTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("up arrow");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), 15.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 1);
}

TEST_F(ForeverMovementTest, DownArrowTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("down arrow");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), -15.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 1);
}

TEST_F(ForeverMovementTest, LeftArrowTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("left arrow");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), -15.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 1);
}

TEST_F(ForeverMovementTest, RightArrowTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("right arrow");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), 15.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), 0.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 1);
}

TEST_F(ForeverMovementTest, RightUpSpaceTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("right arrow");
    pi.keys_down.push_back("up arrow");
    pi.keys_down.push_back("space");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), 45.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), 45.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 0);
}

TEST_F(ForeverMovementTest, LeftDownSpaceTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.keys_down.push_back("r");
    engine->tick(&pi);
    pi.keys_down.clear();

    pi.keys_down.push_back("left arrow");
    pi.keys_down.push_back("down arrow");
    pi.keys_down.push_back("space");
    for (int i = 0; i < 3; i++) engine->tick(&pi);

    ASSERT_EQ(project->sprites.at(0).get_x(), -45.0);
    ASSERT_EQ(project->sprites.at(0).get_y(), -45.0);
    ASSERT_EQ(project->sprites.at(0).get_current_costume(), 0);
}