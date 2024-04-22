#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../src/FileHandler.hpp"
#include "../../src/Project.hpp"
#include "../../src/engine/Engine.hpp"

class GhostTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("ghosttest/");
        FileHandler sb3 = FileHandler("ghosttest.sb3", *temp_dir);
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
};

Project* GhostTest::project = nullptr;
std::string* GhostTest::temp_dir = nullptr;
EngineFunctions::Engine* GhostTest::engine = nullptr;

TEST_F(GhostTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(GhostTest, ChainTest) { ASSERT_EQ(engine->TOTAL_CHAINS, 5); }

TEST_F(GhostTest, Ghost90Test) {
    ASSERT_EQ(engine->get_target_by_name("Sprite4").get_effect("ghost"), 90);
}

TEST_F(GhostTest, Ghost75Test) {
    ASSERT_EQ(engine->get_target_by_name("Sprite1").get_effect("ghost"), 75);
}

TEST_F(GhostTest, Ghost50Test) {
    ASSERT_EQ(engine->get_target_by_name("Sprite2").get_effect("ghost"), 50);
}

TEST_F(GhostTest, Ghost25Test) {
    ASSERT_EQ(engine->get_target_by_name("Sprite3").get_effect("ghost"), 25);
}

TEST_F(GhostTest, Ghost10Test) {
    ASSERT_EQ(engine->get_target_by_name("Sprite5").get_effect("ghost"), 10);
}