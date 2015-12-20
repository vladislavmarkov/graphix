#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gfx/application.h>
#include <gfx/window.h>
#include <sstream>

#include "exception.h"
#include "window_impl.h"

using std::invalid_argument;
using std::runtime_error;
using std::stringstream;

namespace gfx{

namespace { // anonymous

void glfw3_error_callback(int errcode, const char *description){
    stringstream errmsg;
    errmsg
        << "err. code: " << errcode << ", err. message: " << description;
    throw glfw3_error(errmsg.str().c_str());
}

} // anonymous

int run(window &main_window){
    window_impl &main_window_impl =
        dynamic_cast<window_impl&>(main_window);

    GLFWwindow *handle = main_window_impl.get_handle();

    glfwMakeContextCurrent(handle);

    glfwSetErrorCallback(glfw3_error_callback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()){
        throw glew_error("failed to initialize glew");
    }

    while (!glfwWindowShouldClose(handle)){
        main_window_impl.draw();

        glfwSwapBuffers(handle);
        glfwWaitEvents();
    }

    return 0;
}

}
