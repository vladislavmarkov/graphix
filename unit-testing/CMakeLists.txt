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
    src/application.hpp
    src/unit_testing_app.cpp
    src/window.hpp
)

target_include_directories(unit_testing_app
    PUBLIC graphixlib ${GTEST_INCLUDE_DIRS}
    PRIVATE src
)

target_link_libraries(unit_testing_app
    graphixlib
    ${GTEST_BOTH_LIBRARIES}
    pthread
)

add_test(
    NAME unit_testing_app
    COMMAND unit_testing_app
)
