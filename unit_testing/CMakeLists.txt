project(unit_testing_app)
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)

add_definitions(
    "-std=gnu++11"
    "-Wall"
    "-W"
    "-pedantic"
    "-Wextra"
    "-Wconversion"
    "-Winit-self"
    "-Woverloaded-virtual"
    "-Wunreachable-code"
)

add_executable(unit_testing_app
    src/unit_testing_app.cpp
)

target_include_directories(unit_testing_app
    PUBLIC graphix ${GTEST_INCLUDE_DIRS}
    PRIVATE src
)

link_directories(graphix)

target_link_libraries(unit_testing_app
    graphix
    ${GTEST_BOTH_LIBRARIES}
    pthread
)

add_test(
    NAME unit_testing_app
    COMMAND unit_testing_app
)
