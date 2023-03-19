cmake_minimum_required(VERSION 3.11)
project(itch)
include(FetchContent)

find_program(7zip 7z REQUIRED) # install with `sudo scoop install 7zip` on windows
find_program(imagemagick magick REQUIRED) # install with `sudo scoop install imagemagick` on windows

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
message("finished fetching json")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.*pp)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json sfml-system sfml-audio sfml-graphics sfml-window)

set (BUILD_TESTING TRUE)
if (BUILD_TESTING)
    add_subdirectory(test)
endif()

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()