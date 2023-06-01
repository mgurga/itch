cmake_minimum_required(VERSION 3.11)
project(itch)
include(FetchContent)

set(BUILD_NETWORK_SUPPORT true CACHE BOOL "build networking library to download scratch projects")
add_compile_definitions(BUILD_NETWORK_SUPPORT=${BUILD_NETWORK_SUPPORT})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_program(imagemagick magick REQUIRED) # install with `sudo scoop install imagemagick` on windows

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

if(WIN32)
    message("fetching sfml...")
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    message("finished fetching sfml")
elseif()
    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
endif()

message("fetching json...")
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2)
FetchContent_MakeAvailable(json)
set_target_properties(nlohmann_json PROPERTIES INTERFACE_COMPILE_DEFINITIONS "JSON_DIAGNOSTICS=1;JSON_USE_IMPLICIT_CONVERSIONS=1")
message("finished fetching json")

message("fetching cli11...")
FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.2.0)
FetchContent_MakeAvailable(cli11)
message("finished fetching cli11")

message("fetching zip...")
FetchContent_Declare(
    zip
    GIT_REPOSITORY https://github.com/kuba--/zip
    GIT_TAG v0.2.6)
FetchContent_MakeAvailable(zip)
message("finished fetching zip")

if (BUILD_NETWORK_SUPPORT)
    message("fetching cpr...")
    FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
    FetchContent_MakeAvailable(cpr)
    message("finished fetching cpr")
endif()

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.*pp)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json sfml-system sfml-audio sfml-graphics sfml-window CLI11::CLI11 zip)
if (BUILD_NETWORK_SUPPORT)
    target_link_libraries(${PROJECT_NAME} cpr::cpr)
endif()

set (BUILD_TESTING TRUE)
if (BUILD_TESTING)
    add_subdirectory(test)
endif()

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

file(GLOB_RECURSE ASSETS ${PROJECT_SOURCE_DIR}/assets/*)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSETS} $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)