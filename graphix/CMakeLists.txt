project(graphixlib)
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

add_library(graphixlib SHARED
    public/gfx/graphix.h
    public/gfx/window.h
    src/window.cpp
    src/window_impl.h
)

set_target_properties(graphixlib
    PROPERTIES OUTPUT_NAME graphix
)

target_include_directories(graphixlib
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

target_link_libraries(graphixlib
    ${GLEW_LIBRARIES}
    ${GLFW3_LIBRARIES}
)

file(GLOB gfx_include_files
    "${CMAKE_CURRENT_SOURCE_DIR}/public/gfx/*.h"
)

install(FILES ${gfx_include_files} DESTINATION include/gfx)

install(TARGETS graphixlib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(CPACK_PACKAGE_NAME "libgraphix-dev")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Vlad Markov <vladislav.u.markov@gmail.com>")

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 1)

set(CPACK_PACKAGE_FILE_NAME
"libgraphix-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-dev"
)

set(CPACK_STRIP_FILES FALSE)

add_custom_target(deb_package)

add_custom_command(
    TARGET deb_package
    COMMAND make package
    COMMAND mkdir -p repaired_package
    COMMAND dpkg-deb -x ../${CPACK_PACKAGE_FILE_NAME}.deb repaired_package
    COMMAND dpkg-deb --control ../${CPACK_PACKAGE_FILE_NAME}.deb repaired_package/DEBIAN
    COMMAND rm ../${CPACK_PACKAGE_FILE_NAME}.deb
    COMMAND chmod 0644 repaired_package/DEBIAN/md5sums
    COMMAND find -type d -print0 | xargs -0 chmod 755
    COMMAND fakeroot dpkg -b repaired_package ../${CPACK_PACKAGE_FILE_NAME}.deb
    COMMAND rm -rf repaired_package
    WORKING_DIRECTORY ${GRAPHIX_MAIN_SOURCE_DIR}
)

include(CPack)