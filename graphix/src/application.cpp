#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gfx/application.h>
#include <gfx/window.h>
#include <stdexcept>

#include "window_impl.h"

using std::invalid_argument;
using std::runtime_error;

namespace gfx{

int run(window &main_window){
    window_impl &main_window_impl =
        dynamic_cast<window_impl&>(main_window);

    GLFWwindow *handle = main_window_impl.handle_;

    glfwMakeContextCurrent(handle);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()){
        throw runtime_error("failed to initialize glew");
    }

    while (!glfwWindowShouldClose(handle)){
        // TODO

        glfwSwapBuffers(handle);
        glfwWaitEvents();
    }

    return 0;
}

}