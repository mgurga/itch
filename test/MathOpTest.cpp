#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../src/FileHandler.hpp"
#include "../src/Project.hpp"
#include "../src/engine/Engine.hpp"

class MathOpTest : public ::testing::Test {
protected:
    static std::string* temp_dir;
    static Project* project;
    static EngineFunctions::Engine* engine;
    static List solutions;

    static void SetUpTestSuite() {
        temp_dir = new std::string("mathoptest/");
        FileHandler sb3 = FileHandler("mathoptest.sb3", *temp_dir);
        sb3.init(
            [&]() { std::cout << "finished unzipping " << sb3.file_name_no_ext << std::endl; });

        project = new Project(*temp_dir);
        project->load_from_project_json(false);

        engine = new EngineFunctions::Engine(*project);

        engine->tick();
        solutions = engine->get_list_by_name("solutions");
    }

    static void TearDownTestSuite() {
        std::cout << "deleteing " << *temp_dir << " temp directory" << std::endl;
        std::filesystem::remove_all(*temp_dir);
        delete project;
        delete temp_dir;
        delete engine;
    }
};

Project* MathOpTest::project = nullptr;
std::string* MathOpTest::temp_dir = nullptr;
EngineFunctions::Engine* MathOpTest::engine = nullptr;

static const double PI = 3.14159265;
List MathOpTest::solutions = List();

TEST_F(MathOpTest, MetaTest) { ASSERT_EQ(project->meta.semver, "3.0.0"); }

TEST_F(MathOpTest, ChainTest) { ASSERT_EQ(engine->TOTAL_CHAINS, 2); }

TEST_F(MathOpTest, AbsoluteValueTest) {
    ASSERT_TRUE(solutions.at(1).contains_number());
    ASSERT_EQ(solutions.at(1).get_number(), 5);
    ASSERT_TRUE(solutions.at(2).contains_number());
    ASSERT_EQ(solutions.at(2).get_number(), 23.542);
    ASSERT_TRUE(solutions.at(3).contains_number());
    ASSERT_EQ(solutions.at(3).get_number(), 10.0001);
}

TEST_F(MathOpTest, FloorTest) {
    ASSERT_TRUE(solutions.at(4).contains_number());
    ASSERT_EQ(solutions.at(4).get_number(), 10);
    ASSERT_TRUE(solutions.at(5).contains_number());
    ASSERT_EQ(solutions.at(5).get_number(), 12);
}

TEST_F(MathOpTest, CeilingTest) {
    ASSERT_TRUE(solutions.at(6).contains_number());
    ASSERT_EQ(solutions.at(6).get_number(), 10);
    ASSERT_TRUE(solutions.at(7).contains_number());
    ASSERT_EQ(solutions.at(7).get_number(), 16);
}

TEST_F(MathOpTest, SquareRootTest) {
    ASSERT_TRUE(solutions.at(8).contains_number());
    ASSERT_EQ(solutions.at(8).get_number(), 5);
    ASSERT_TRUE(solutions.at(9).contains_number());
    ASSERT_EQ(solutions.at(9).get_number(), std::sqrt(1.5));
}

TEST_F(MathOpTest, SinTest) {
    ASSERT_TRUE(solutions.at(10).contains_number());
    ASSERT_EQ(solutions.at(10).get_number(), 0);
    ASSERT_TRUE(solutions.at(11).contains_number());
    ASSERT_NEAR(solutions.at(11).get_number(), std::sin(0.5 * (PI / 180)), 0.000001);
}

TEST_F(MathOpTest, CosTest) {
    ASSERT_TRUE(solutions.at(12).contains_number());
    ASSERT_NEAR(solutions.at(12).get_number(), std::cos(180 * PI / 180), 0.000001);
    ASSERT_TRUE(solutions.at(13).contains_number());
    ASSERT_NEAR(solutions.at(13).get_number(), std::cos(300 * PI / 180), 0.000001);
}

TEST_F(MathOpTest, TanTest) {
    ASSERT_TRUE(solutions.at(14).contains_number());
    ASSERT_NEAR(solutions.at(14).get_number(), std::tan(180 * PI / 180), 0.000001);
    ASSERT_TRUE(solutions.at(15).contains_number());
    ASSERT_NEAR(solutions.at(15).get_number(), std::tan(100 * PI / 180), 0.000001);
}

TEST_F(MathOpTest, AsinTest) {
    ASSERT_TRUE(solutions.at(16).contains_number());
    ASSERT_NEAR(solutions.at(16).get_number(), 90, 0.000001);
}

TEST_F(MathOpTest, AcosTest) {
    ASSERT_TRUE(solutions.at(17).contains_number());
    ASSERT_NEAR(solutions.at(17).get_number(), 0, 0.000001);
}

TEST_F(MathOpTest, AtanTest) {
    ASSERT_TRUE(solutions.at(18).contains_number());
    ASSERT_NEAR(solutions.at(18).get_number(), 45, 0.000001);
}

TEST_F(MathOpTest, AsinNanTest) {
    ASSERT_TRUE(solutions.at(19).contains_number());
    ASSERT_TRUE(solutions.at(19).is_nan());
    ASSERT_TRUE(solutions.at(19).get_number() != solutions.at(19).get_number());
}

TEST_F(MathOpTest, NaturalLogTest) {
    ASSERT_TRUE(solutions.at(20).contains_number());
    ASSERT_NEAR(solutions.at(20).get_number(), 1, 0.000001);
}

TEST_F(MathOpTest, LogTest) {
    ASSERT_TRUE(solutions.at(21).contains_number());
    ASSERT_NEAR(solutions.at(21).get_number(), 0, 0.000001);
}

TEST_F(MathOpTest, EulerExponentTest) {
    ASSERT_TRUE(solutions.at(22).contains_number());
    ASSERT_NEAR(solutions.at(22).get_number(), 7.38905609893065, 0.000001);
}

TEST_F(MathOpTest, Power10Test) {
    ASSERT_TRUE(solutions.at(23).contains_number());
    ASSERT_TRUE(solutions.at(23).is_infinity());
}