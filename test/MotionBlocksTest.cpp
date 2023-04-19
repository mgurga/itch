#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "../src/Project.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/FileHandler.hpp"
#include "../src/blocks/Opcodes.hpp"

class MotionBlocksTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("motionblocks/");
        FileHandler sb3 = FileHandler("motionblocks.sb3", *temp_dir);
        sb3.init([&] () {
            std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl;
        });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);

        engine = new EngineFunctions::Engine(*project);
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
        delete engine;
    }
};

Project* MotionBlocksTest::project = nullptr;
std::string* MotionBlocksTest::temp_dir = nullptr;
EngineFunctions::Engine* MotionBlocksTest::engine = nullptr;

TEST_F(MotionBlocksTest, MetaTest) {
    ASSERT_EQ(project->meta.semver, "3.0.0");
}

TEST_F(MotionBlocksTest, ChainTest) {
    ASSERT_EQ(engine->TOTAL_CHAINS, 11);
}

TEST_F(MotionBlocksTest, OperatorsTest) {
    ASSERT_EQ(engine->reporters.size(), 6);
}

TEST_F(MotionBlocksTest, UpPressTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("up arrow");
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi); // second tick to process broadcasts
    ASSERT_EQ(project->sprites.at(0).x, 10.0);
    ASSERT_EQ(project->sprites.at(0).y, 20.0);
    ASSERT_TRUE(engine->say_logs.at(0).message.find("Going to x:") != std::string::npos);
    ASSERT_EQ(engine->say_logs.at(0).duration, 1);
}

TEST_F(MotionBlocksTest, ResetTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("z");
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).x, 0.0);
    ASSERT_EQ(project->sprites.at(0).y, 0.0);
    ASSERT_EQ(project->sprites.at(0).direction, 90.0);
    ASSERT_EQ(engine->variant_str(engine->get_var_by_name("var").val()), "0");
}

TEST_F(MotionBlocksTest, ThreeUpPressTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("up arrow");
    engine->tick(&pi);
    engine->tick(&pi);
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi); // second tick to process broadcasts
    ASSERT_EQ(project->sprites.at(0).x, 30.0);
    ASSERT_EQ(project->sprites.at(0).y, 60.0);
}

TEST_F(MotionBlocksTest, ResetTest2) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("z");
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).x, 0.0);
    ASSERT_EQ(project->sprites.at(0).y, 0.0);
    ASSERT_EQ(project->sprites.at(0).direction, 90.0);
    ASSERT_EQ(engine->variant_str(engine->get_var_by_name("var").val()), "0");
}

TEST_F(MotionBlocksTest, GoToMouseTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("m");
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).x, 25.0);
    ASSERT_EQ(project->sprites.at(0).y, 25.0);
}

TEST_F(MotionBlocksTest, ChangeDirectionTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    pi.pressed.push_back("m");
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi);
    pi.pressed.push_back("right arrow");
    engine->tick(&pi);
    engine->tick(&pi);
    pi.pressed.clear();
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).direction, 120.0);
    pi.pressed.push_back("left arrow");
    engine->tick(&pi);
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).direction, 90.0);
}

TEST_F(MotionBlocksTest, MoveStepsTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    pi.pressed.push_back("space");
    engine->tick(&pi);
    engine->tick(&pi);
    ASSERT_EQ(project->sprites.at(0).x, 20.0);
    ASSERT_EQ(project->sprites.at(0).y, 0.0);
}

TEST_F(MotionBlocksTest, RandomPositionTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    pi.pressed.push_back("z");
    bool changed = false;

    engine->tick(&pi);
    pi.pressed.clear();
    pi.pressed.push_back("r");

    engine->tick(&pi);
    if (project->sprites.at(0).x != 0.0 && project->sprites.at(0).y != 0.0)
        changed = true;
    engine->tick(&pi);
    if (project->sprites.at(0).x != 0.0 && project->sprites.at(0).y != 0.0)
        changed = true;
    engine->tick(&pi);
    if (project->sprites.at(0).x != 0.0 && project->sprites.at(0).y != 0.0)
        changed = true;

    ASSERT_TRUE(changed);
}