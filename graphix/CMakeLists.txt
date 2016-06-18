project(graphixapp VERSION 0.0.1)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_library(MSGPACK_LIB msgpack)
find_library(ZMQ_LIB zmq)
find_package(Boost 1.54 REQUIRED)
find_package(SDL2 REQUIRED)
find_path(MSGPACK_INCLUDE_DIRS msgpack.hpp
    /usr/local/include
    /usr/include
)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

add_definitions(
    "-std=gnu++14"
    "-Werror"
    "-Wall"
    "-Wextra"
    "-W"
    "-pedantic"
    "-Wconversion"
    "-Winit-self"
    "-Woverloaded-virtual"
    "-Wunreachable-code"
)

set(ALL_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/application.hpp
    ${PROJECT_SOURCE_DIR}/src/application_impl.cpp
    ${PROJECT_SOURCE_DIR}/src/application_impl.hpp
    ${PROJECT_SOURCE_DIR}/src/error.hpp
    ${PROJECT_SOURCE_DIR}/src/graphix.cpp
    ${PROJECT_SOURCE_DIR}/src/message.cpp
    ${PROJECT_SOURCE_DIR}/src/message.hpp
    ${PROJECT_SOURCE_DIR}/src/window.hpp
    ${PROJECT_SOURCE_DIR}/src/window_impl.cpp
    ${PROJECT_SOURCE_DIR}/src/window_impl.hpp
)

add_executable(graphixapp ${ALL_SOURCE_FILES})

set(GRAPHIXAPP_PACKAGE_NAME graphix)

set_target_properties(graphixapp
    PROPERTIES OUTPUT_NAME ${GRAPHIXAPP_PACKAGE_NAME}
)

target_include_directories(graphixapp
PRIVATE
    ${MSGPACK_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    cppzmq
)

target_link_libraries(graphixapp
PRIVATE
    ${MSGPACK_LIB}
    ${SDL2_LIBRARIES}
    ${ZMQ_LIB}
    pthread
)

add_custom_target(cppcheck
    COMMAND /usr/bin/cppcheck
    --enable=all
    --suppress=missingIncludeSystem
    --std=c++11
    --template="[{severity}][{id}] {message} {callstack} \(on {file}:{line}\)"
    --verbose
    --quiet
    ${ALL_SOURCE_FILES}
)

add_custom_target(clangformat
    COMMAND /usr/bin/clang-format-3.8
    -style=file
    -i ${ALL_SOURCE_FILES}
)

set(SDL2_REQUIRED_VERSION "SDL2 >= 2.0.4")

install(TARGETS graphixapp RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

set(CPACK_PACKAGE_NAME "graphix")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Vlad Markov <vladislav.u.markov@gmail.com>")
set(CPACK_PACKAGE_FILE_NAME "${GRAPHIXAPP_PACKAGE_NAME}-${PROJECT_VERSION}")
set(CPACK_STRIP_FILES TRUE)
set(PKG_CONFIG_REQUIRES "${SDL2_REQUIRED_VERSION}")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${GRAPHIXAPP_PACKAGE_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${GRAPHIXAPP_PACKAGE_NAME}.pc
    @ONLY
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${GRAPHIXAPP_PACKAGE_NAME}.pc"
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
