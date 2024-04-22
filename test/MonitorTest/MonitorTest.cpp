#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

#include "../../src/FileHandler.hpp"
#include "../../src/Project.hpp"
#include "../../src/engine/Engine.hpp"

class MonitorTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;

    static void SetUpTestSuite() {
        temp_dir = new std::string("monitortest/");
        FileHandler sb3 = FileHandler("monitortest.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);

        engine = new EngineFunctions::Engine(*project);

        EMPTY_PLAYER_INFO(pi);
        engine->tick(&pi);
        pi.pressed.push_back("space");
        engine->tick(&pi);
        engine->tick(&pi);
        engine->tick(&pi);
        engine->tick(&pi);
        engine->tick(&pi);
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
        delete engine;
    }

    static ScratchMonitor& get_monitor_by_name(std::string name) {
        for (ScratchMonitor& m : project->monitors)
            if (m.display_name == name) return m;
        throw std::invalid_argument("monitor with name '" + name + "' does not exist");
    }
};

Project* MonitorTest::project = nullptr;
std::string* MonitorTest::temp_dir = nullptr;
EngineFunctions::Engine* MonitorTest::engine = nullptr;

TEST_F(MonitorTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(MonitorTest, VariableTest) {
    ASSERT_EQ(get_monitor_by_name("variable name and value").values.at(0), "5");
    ASSERT_EQ(get_monitor_by_name("variable slider").values.at(0), "5");
    ASSERT_EQ(get_monitor_by_name("variable display only").values.at(0), "5");
    ASSERT_EQ(get_monitor_by_name("variable change").values.at(0), "1");
}

TEST_F(MonitorTest, ChangeVariableTest) {
    EMPTY_PLAYER_INFO(pi);
    pi.pressed.push_back("up arrow");
    engine->tick(&pi);
    ASSERT_EQ(get_monitor_by_name("variable change").values.at(0), "2");
    pi.pressed.clear();
    pi.pressed.push_back("down arrow");
    engine->tick(&pi);
    ASSERT_EQ(get_monitor_by_name("variable change").values.at(0), "1");
}

TEST_F(MonitorTest, SensingMonitorTest) {
    EMPTY_PLAYER_INFO(pi);
    engine->tick(&pi);
    ASSERT_EQ(get_monitor_by_name("username").values.at(0), "");
    ASSERT_NEAR(std::stod(get_monitor_by_name("timer").values.at(0)), 1.5, 1.5);
    ASSERT_NEAR(std::stod(get_monitor_by_name("year").values.at(0)), 2023.0, 100.0);
    ASSERT_NEAR(std::stod(get_monitor_by_name("month").values.at(0)), 6.0, 7.0);
    ASSERT_NEAR(std::stod(get_monitor_by_name("day of week").values.at(0)), 4.0, 5.0);
    ASSERT_NEAR(std::stod(get_monitor_by_name("hour").values.at(0)), 12.0, 12.0);
    ASSERT_NEAR(std::stod(get_monitor_by_name("minute").values.at(0)), 30.0, 31.0);
    ASSERT_EQ(get_monitor_by_name("answer").values.at(0), "");
    ASSERT_EQ(get_monitor_by_name("loudness").values.at(0), "-1");
}

TEST_F(MonitorTest, MotionMonitorTest) {
    ASSERT_EQ(get_monitor_by_name("Sprite1: x position").values.at(0), "0");
    ASSERT_EQ(get_monitor_by_name("Sprite1: y position").values.at(0), "0");
    ASSERT_EQ(get_monitor_by_name("Sprite1: direction").values.at(0), "90");
}

TEST_F(MonitorTest, LooksMonitorTest) {
    ASSERT_EQ(get_monitor_by_name("Sprite1: size").values.at(0), "100");
    ASSERT_EQ(get_monitor_by_name("Sprite1: costume number").values.at(0), "1");
    ASSERT_EQ(get_monitor_by_name("Sprite1: costume name").values.at(0), "costume1");
    ASSERT_EQ(get_monitor_by_name("backdrop number").values.at(0), "1");
    ASSERT_EQ(get_monitor_by_name("backdrop name").values.at(0), "backdrop1");
}

TEST_F(MonitorTest, SoundMonitorTest) {
    ASSERT_EQ(get_monitor_by_name("Sprite1: volume").values.at(0), "100");
}

TEST_F(MonitorTest, ListMonitorTest) {
    ASSERT_EQ(get_monitor_by_name("visible list").values.at(0), "hello");
    ASSERT_EQ(get_monitor_by_name("visible list").values.at(1), "world");
    ASSERT_EQ(get_monitor_by_name("visible list").values.size(), 2);
}