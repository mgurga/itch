#include "../src/Project.hpp"
#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}