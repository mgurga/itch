#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"

class AllBlocksTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;

    static void SetUpTestSuite() {
        temp_dir = new std::string("allblocks/");
        FileHandler sb3 = FileHandler("allblocks.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

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

Project* AllBlocksTest::project = nullptr;
std::string* AllBlocksTest::temp_dir = nullptr;

TEST_F(AllBlocksTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }