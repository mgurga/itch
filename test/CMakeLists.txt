set(TEST_PROJECT_NAME test_${PROJECT_NAME})

message("started fetching googletest...")
include(FetchContent)
cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
    googletest
    # v 1.11.0
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
message("finished fetching googletest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB_RECURSE TESTFILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
file(GLOB_RECURSE SRCFILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SRCFILES ${PROJECT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE SB3FILES ${PROJECT_SOURCE_DIR}/test/*.sb3)

add_executable(${TEST_PROJECT_NAME} ${TESTFILES} ${SRCFILES})
target_link_libraries(${TEST_PROJECT_NAME} gtest_main sfml-system sfml-audio sfml-graphics nlohmann_json::nlohmann_json)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test_${PROJECT_NAME}> $<TARGET_FILE_DIR:test_${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:test_${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SB3FILES} $<TARGET_FILE_DIR:test_${PROJECT_NAME}> COMMAND_EXPAND_LISTS)

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})