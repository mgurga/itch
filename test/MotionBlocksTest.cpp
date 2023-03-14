#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Project.hpp"
#include "../src/FileHandler.hpp"
#include "../src/blocks/Opcodes.hpp"

using ::testing::AnyOf;

class MotionBlocksTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;

    static void SetUpTestSuite() {
        temp_dir = new std::string("motionblocks/");
        FileHandler sb3 = FileHandler("motionblocks.sb3", *temp_dir);
        sb3.init([&] () {
            std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl;
        });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
    }
};

Project* MotionBlocksTest::project = nullptr;
std::string* MotionBlocksTest::temp_dir = nullptr;

TEST_F(MotionBlocksTest, MetaTest) {
    ASSERT_EQ(project->meta.semver, "3.0.0");
}