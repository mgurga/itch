#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../src/FileHandler.hpp"
#include "../../src/Project.hpp"
#include "../../src/engine/Engine.hpp"

class WaitUntilTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("waituntil/");
        FileHandler sb3 = FileHandler("waituntil.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

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

Project* WaitUntilTest::project = nullptr;
std::string* WaitUntilTest::temp_dir = nullptr;
EngineFunctions::Engine* WaitUntilTest::engine = nullptr;

TEST_F(WaitUntilTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(WaitUntilTest, InitalVariableTest) {
    EMPTY_PLAYER_INFO(pi);
    engine->tick(&pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 0);
}

TEST_F(WaitUntilTest, SpaceTapTest) {
    engine->get_var_by_name("my variable") = 0;
    EMPTY_PLAYER_INFO(empty_pi);
    EMPTY_PLAYER_INFO(space_pi);
    space_pi.keys_down.push_back("space");

    engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 1);

    engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 2);

    engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 3);
}

TEST_F(WaitUntilTest, SpaceHoldTest) {
    engine->get_var_by_name("my variable") = 0;
    EMPTY_PLAYER_INFO(empty_pi);
    EMPTY_PLAYER_INFO(space_pi);
    space_pi.keys_down.push_back("space");

    for (int i = 0; i < 10; i++) engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 1);

    for (int i = 0; i < 50; i++) engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 2);

    for (int i = 0; i < 100; i++) engine->tick(&space_pi);
    engine->tick(&empty_pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 3);
}