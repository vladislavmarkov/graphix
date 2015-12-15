#include <gfx/application.h>
#include <gfx/window.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "window_impl.h"

using std::invalid_argument;

namespace gfx{

int run(window *main_window){
    if (!main_window){
        throw invalid_argument("main window is null");
    }

    window_impl *main_window_impl = dynamic_cast<window_impl*>(main_window);

    while (!glfwWindowShouldClose(main_window_impl->handle_)){
        glfwSwapBuffers(main_window_impl->handle_);
        glfwPollEvents();
    }

    return 0;
}

}