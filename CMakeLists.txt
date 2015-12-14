cmake_minimum_required(VERSION 3.2)
project(graphix_main)

enable_testing()

add_subdirectory(documentation)
add_subdirectory(graphix)
add_subdirectory(unit_testing)

add_dependencies(documentation graphix)
add_dependencies(unit_testing_app graphix)
