#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "../../src/FileHandler.hpp"
#include "../../src/Project.hpp"
#include "../../src/engine/Engine.hpp"

class ListTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("listtest/");
        FileHandler sb3 = FileHandler("listtest.sb3", *temp_dir);
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

Project* ListTest::project = nullptr;
std::string* ListTest::temp_dir = nullptr;
EngineFunctions::Engine* ListTest::engine = nullptr;

TEST_F(ListTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(ListTest, ChainTest) { ASSERT_EQ(engine->TOTAL_CHAINS, 2); }

TEST_F(ListTest, InitialListTest) {
    auto list = engine->get_list_by_name("my list");
    ASSERT_EQ(list.length(), 3);
    ASSERT_EQ(list.at(1).get_string(), "initial");
    ASSERT_EQ(list.at(2).get_string(), "list");
    ASSERT_EQ(list.at(3).get_string(), "");
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 1.0);
}

TEST_F(ListTest, FinalListTest) {
    engine->tick();
    auto list = engine->get_list_by_name("my list");
    ASSERT_EQ(list.length(), 4);
    ASSERT_EQ(list.at(1).get_string(), "a");
    ASSERT_EQ(list.at(2).get_string(), "REPLACED");
    ASSERT_EQ(list.at(3).get_string(), "INSERTED");
    ASSERT_EQ(list.at(4).get_string(), "c");
}

TEST_F(ListTest, MessageLogTest) {
    engine->tick();
    ASSERT_EQ(engine->say_logs.at(0).message, "mylist[1]: a");
    engine->tick();
    ASSERT_EQ(engine->say_logs.at(0).message, "mylist[2]: REPLACED");
    engine->tick();
    ASSERT_EQ(engine->say_logs.at(0).message, "mylist[3]: INSERTED");
    engine->tick();
    ASSERT_EQ(engine->say_logs.at(0).message, "mylist[4]: c");
    ASSERT_EQ(engine->get_var_by_name("my variable").val().get_number(), 5.0);
}