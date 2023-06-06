#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"
#include "../src/blocks/Opcodes.hpp"

using ::testing::AnyOf;

class BasicMovementTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;

    static void SetUpTestSuite() {
        temp_dir = new std::string("basicmovement/");
        FileHandler sb3 = FileHandler("basicmovement.sb3", *temp_dir);
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

Project* BasicMovementTest::project = nullptr;
std::string* BasicMovementTest::temp_dir = nullptr;

TEST_F(BasicMovementTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(BasicMovementTest, TargetTest) {
    ASSERT_EQ(project->stage.isStage(), true);
    ASSERT_EQ(project->stage.get_name(), "Stage");

    ASSERT_EQ(project->sprites[0].isStage(), false);
    ASSERT_EQ(project->sprites[0].get_name(), "Sprite1");
}

TEST_F(BasicMovementTest, SoundTest) {
    ASSERT_EQ(project->stage.sounds[0].assetId, "83a9787d4cb6f3b7632b4ddfebf74367");
    ASSERT_EQ(project->stage.sounds[0].md5ext, "83a9787d4cb6f3b7632b4ddfebf74367.wav");
    ASSERT_EQ(project->stage.sounds[0].dataFormat, "wav");
    ASSERT_EQ(project->stage.sounds[0].name, "pop");
    ASSERT_EQ(project->stage.sounds[0].rate, 44100);
    ASSERT_EQ(project->stage.sounds[0].sampleCount, 1032);
}

TEST_F(BasicMovementTest, ChainTest) {
    ASSERT_EQ(project->sprites[0].chains.size(), 4);

    ASSERT_EQ(project->sprites[0].chains[0].activatable, true);
    ASSERT_EQ(project->sprites[0].chains[1].activatable, true);
    ASSERT_EQ(project->sprites[0].chains[2].activatable, true);
    ASSERT_EQ(project->sprites[0].chains[3].activatable, true);

    ASSERT_EQ(project->sprites[0].chains[0].links[0].opcode.opcode, WHEN_KEY_PRESSED);
    ASSERT_THAT(project->sprites[0].chains[0].links[1].opcode.opcode,
                AnyOf(CHANGE_Y_BY, POINT_IN_DIRECTION));

    ASSERT_EQ(project->sprites[0].chains[1].links[0].opcode.opcode, WHEN_KEY_PRESSED);
    ASSERT_THAT(project->sprites[0].chains[1].links[1].opcode.opcode,
                AnyOf(CHANGE_Y_BY, POINT_IN_DIRECTION));
}