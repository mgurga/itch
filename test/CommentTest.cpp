#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"

class CommentTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;

    static void SetUpTestSuite() {
        temp_dir = new std::string("commenttest/");
        FileHandler sb3 = FileHandler("commenttest.sb3", *temp_dir);
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

Project* CommentTest::project = nullptr;
std::string* CommentTest::temp_dir = nullptr;

TEST_F(CommentTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(CommentTest, CommentCountTest) {
    ASSERT_EQ(project->stage.get_comments().size(), 1);
    ASSERT_EQ(project->sprites.at(0).get_comments().size(), 3);
}

TEST_F(CommentTest, UntetheredCommentTest) {
    ASSERT_EQ(project->stage.get_comments().begin()->first, "adRfUf4e5P!V;lRa1WX3");
    ASSERT_FALSE(project->stage.get_comments().begin()->second.get_block_id().has_value());
    ASSERT_EQ(project->stage.get_comments().begin()->second.get_width(), 200);
    ASSERT_EQ(project->stage.get_comments().begin()->second.get_height(), 200);
    ASSERT_EQ(project->stage.get_comments().begin()->second.get_text(),
              "untethered backdrop comment");
}

TEST_F(CommentTest, TetheredComment1Test) {
    auto sprcomments = project->sprites.at(0).get_comments();
    ASSERT_FALSE(sprcomments.find("-^+2+IM![8d;%vNS]gYc") == sprcomments.end());
    ASSERT_EQ(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_block_id().value_or("(no block id)"),
              "INB;R@;$[1EDgW0q]CK{");
    ASSERT_EQ(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_text(), "flag start for Sprite1");
    ASSERT_NEAR(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_x(), 413.341435, 0.1);
    ASSERT_NEAR(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_y(), 218.22222, 0.1);
    ASSERT_NEAR(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_width(), 182.22229, 0.1);
    ASSERT_NEAR(sprcomments["-^+2+IM![8d;%vNS]gYc"].get_height(), 85.92593, 0.1);
    ASSERT_FALSE(sprcomments["-^+2+IM![8d;%vNS]gYc"].is_minimized());
}

TEST_F(CommentTest, TetheredComment2Test) {
    auto sprcomments = project->sprites.at(0).get_comments();
    ASSERT_FALSE(sprcomments.find("8%ddt,V}YgLbJ55o~aO_") == sprcomments.end());
    ASSERT_EQ(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_block_id().value_or("(no block id)"),
              "ljWF).KL$i8SBZ.X:4X2");
    ASSERT_EQ(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_text(), "set initial position");
    ASSERT_NEAR(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_x(), -19.98570, 0.1);
    ASSERT_NEAR(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_y(), 270.66666, 0.1);
    ASSERT_NEAR(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_width(), 197.03704, 0.1);
    ASSERT_NEAR(sprcomments["8%ddt,V}YgLbJ55o~aO_"].get_height(), 96.29629, 0.1);
    ASSERT_FALSE(sprcomments["8%ddt,V}YgLbJ55o~aO_"].is_minimized());
}

TEST_F(CommentTest, TetheredComment3Test) {
    auto sprcomments = project->sprites.at(0).get_comments();
    ASSERT_FALSE(sprcomments.find("niazQ5tO#kek@N[s8U.b") == sprcomments.end());
    ASSERT_EQ(sprcomments["niazQ5tO#kek@N[s8U.b"].get_block_id().value_or("(no block id)"),
              "{;y!y(u*v|Rg3I?1Hb0|");
    ASSERT_EQ(sprcomments["niazQ5tO#kek@N[s8U.b"].get_text(), "final block");
    ASSERT_NEAR(sprcomments["niazQ5tO#kek@N[s8U.b"].get_x(), 378.53004, 0.1);
    ASSERT_NEAR(sprcomments["niazQ5tO#kek@N[s8U.b"].get_y(), 362.22222, 0.1);
    ASSERT_NEAR(sprcomments["niazQ5tO#kek@N[s8U.b"].get_width(), 109.62963, 0.1);
    ASSERT_NEAR(sprcomments["niazQ5tO#kek@N[s8U.b"].get_height(), 88.88888, 0.1);
    ASSERT_FALSE(sprcomments["niazQ5tO#kek@N[s8U.b"].is_minimized());
}

TEST_F(CommentTest, ScratchBlockCommentTest) {
    ASSERT_EQ(project->sprites.at(0).blocks.at(1).opcode, "event_whenflagclicked");
    ASSERT_TRUE(project->sprites.at(0).blocks.at(1).comment_id.has_value());
    ASSERT_EQ(project->sprites.at(0).blocks.at(1).comment_id.value(), "-^+2+IM![8d;%vNS]gYc");

    ASSERT_EQ(project->sprites.at(0).blocks.at(2).opcode, "motion_gotoxy");
    ASSERT_TRUE(project->sprites.at(0).blocks.at(2).comment_id.has_value());
    ASSERT_EQ(project->sprites.at(0).blocks.at(2).comment_id.value(), "8%ddt,V}YgLbJ55o~aO_");

    ASSERT_EQ(project->sprites.at(0).blocks.at(0).opcode, "motion_movesteps");
    ASSERT_FALSE(project->sprites.at(0).blocks.at(0).comment_id.has_value());
}