#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

#include "../src/Project.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/FileHandler.hpp"

class OpsPerSecTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("opspersec/");
        FileHandler sb3 = FileHandler("opspersec.sb3", *temp_dir);
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

Project* OpsPerSecTest::project = nullptr;
std::string* OpsPerSecTest::temp_dir = nullptr;
EngineFunctions::Engine* OpsPerSecTest::engine = nullptr;

TEST_F(OpsPerSecTest, MetaTest) {
    ASSERT_EQ(project->meta.semver, "3.0.0");
}

TEST_F(OpsPerSecTest, ChainTest) {
    ASSERT_EQ(engine->TOTAL_CHAINS, 3);
}

TEST_F(OpsPerSecTest, OperatorsTest) {
    ASSERT_EQ(engine->reporters.size(), 0);
}

TEST_F(OpsPerSecTest, InitalVariableTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    engine->tick(&pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 0);
}

TEST_F(OpsPerSecTest, ForeverLoopTest) {
    PlayerInfo pi = PlayerInfo::get_empty_player_info();
    for (int i = 0; i < 10; i++)
        engine->tick(&pi);
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 10);
}