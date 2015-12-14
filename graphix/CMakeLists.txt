project(graphix)
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW3 REQUIRED glfw3)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58)

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

add_library(graphix SHARED
    public/graphix.h
    src/graphix.cpp
)

target_include_directories(graphix
    PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
        public
    PRIVATE
        src
)

link_directories(
    ${GLEW_LIBRARY_DIRS}
    ${GLFW3_LIBRARY_DIRS}
)

target_link_libraries(graphix
    ${GLEW_LIBRARIES}
    ${GLFW3_LIBRARIES}
)
