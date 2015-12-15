cmake_minimum_required(VERSION 3.2)
project(graphix)

enable_testing()

add_subdirectory(documentation)
add_subdirectory(graphix)
add_subdirectory(unit-testing)

add_dependencies(documentation graphixlib)
add_dependencies(unit_testing_app graphixlib documentation)
