project(graphixlib
    VERSION 0.0.1
)

set(PROJECT_DESCRIPTION "Graphix is a OpenGL C++ wrapper library.")

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)

set(ASSIMP_REQUIRED_VERSION "assimp >= 3.2")
set(GLEW_REQUIRED_VERSION "glew >= 1.10.0")
set(GLFW3_REQUIRED_VERSION "glfw3 >= 3.1.2")

pkg_check_modules(ASSIMP REQUIRED ${ASSIMP_REQUIRED_VERSION})
pkg_check_modules(GLEW REQUIRED ${GLEW_REQUIRED_VERSION})
pkg_check_modules(GLFW3 REQUIRED ${GLFW3_REQUIRED_VERSION})

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54)

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
    public/gfx/application.h
    public/gfx/camera.h
    public/gfx/drawable.h
    public/gfx/graphix.h
    public/gfx/key.h
    public/gfx/mesh.h
    public/gfx/scene.h
    public/gfx/shader.h
    public/gfx/window.h
    src/application.cpp
    src/camera.cpp
    src/camera_impl.h
    src/convert_meshes.cpp
    src/convert_meshes.h
    src/dependent.h
    src/exception.h
    src/mesh_impl.h
    src/scene.cpp
    src/scene_impl.h
    src/shader.cpp
    src/window.cpp
    src/window_impl.h
)

set(GRAPHIXLIB_PACKAGE_NAME graphix)

set_target_properties(graphixlib
    PROPERTIES OUTPUT_NAME ${GRAPHIXLIB_PACKAGE_NAME}
)

target_include_directories(graphixlib
    PUBLIC
        ${ASSIMP_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
        public
    PRIVATE
        src
)

link_directories(
    ${ASSIMP_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
    ${GLFW3_LIBRARY_DIRS}
)

target_link_libraries(graphixlib
    ${ASSIMP_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW3_LIBRARIES}
    ${GLFW3_STATIC_LIBRARIES}
)

file(GLOB gfx_include_files
    "${CMAKE_CURRENT_SOURCE_DIR}/public/gfx/*.h"
)

install(FILES ${gfx_include_files} DESTINATION include/gfx)

install(TARGETS graphixlib
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
)

set(CPACK_PACKAGE_NAME "libgraphix-dev")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Vlad Markov <vladislav.u.markov@gmail.com>")

set(CPACK_PACKAGE_FILE_NAME
    "lib${GRAPHIXLIB_PACKAGE_NAME}-${PROJECT_VERSION}-dev"
)

set(CPACK_STRIP_FILES FALSE)

set(PKG_CONFIG_REQUIRES "${ASSIMP_REQUIRED_VERSION} ${GLEW_REQUIRED_VERSION} ${GLFW3_REQUIRED_VERSION}")

set(PKG_CONFIG_LIBDIR "\${prefix}/lib")

set(PKG_CONFIG_INCLUDEDIR "\${prefix}/include")

set(PKG_CONFIG_LIBS "-L\${libdir} -l${GRAPHIXLIB_PACKAGE_NAME}")

set(PKG_CONFIG_CFLAGS "-I\${includedir}")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${GRAPHIXLIB_PACKAGE_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${GRAPHIXLIB_PACKAGE_NAME}.pc
    @ONLY
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${GRAPHIXLIB_PACKAGE_NAME}.pc"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
)

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
