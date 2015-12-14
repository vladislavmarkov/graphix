project(unit_testing_app)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unit_testing_app
    src/unit_testing_app.cpp
)

target_link_libraries(unit_testing_app ${GTEST_BOTH_LIBRARIES} pthread)

add_test(
    NAME all
    COMMAND unit_testing_app
)
