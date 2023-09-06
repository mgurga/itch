#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"
#include "../src/engine/Engine.hpp"

class CloneRunTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("cloneruntest/");
        FileHandler sb3 = FileHandler("cloneruntest.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);

        engine = new EngineFunctions::Engine(*project);

        for (int i = 0; i < 37; i++) engine->tick();
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
        delete engine;
    }
};

Project* CloneRunTest::project = nullptr;
std::string* CloneRunTest::temp_dir = nullptr;
EngineFunctions::Engine* CloneRunTest::engine = nullptr;

TEST_F(CloneRunTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(CloneRunTest, ChainTest) { ASSERT_EQ(engine->TOTAL_CHAINS, 4); }

TEST_F(CloneRunTest, CloneNumberTest) { ASSERT_EQ(engine->clones.size(), 5); }

TEST_F(CloneRunTest, ClonePositionTest) {
    for (int i = 0; i < 5; i++) ASSERT_EQ(engine->clones.at(i).get_x(), 150);

    ASSERT_EQ(engine->clones.at(0).get_y(), 100);
    ASSERT_EQ(engine->clones.at(1).get_y(), 50);
    ASSERT_EQ(engine->clones.at(2).get_y(), 0);
    ASSERT_EQ(engine->clones.at(3).get_y(), -50);
    ASSERT_EQ(engine->clones.at(4).get_y(), -100);
}