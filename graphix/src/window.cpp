#include <gfx/window.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "window_impl.h"

using std::unique_ptr;

namespace gfx{

unique_ptr<window> window::create(
    const std::string &caption,
    size_t width,
    size_t height
){
    static struct guardian__{
        guardian__(){
            if (!glfwInit()){
                glfwTerminate();
                throw std::runtime_error("failed to initialize glfw");
            }
        }

        ~guardian__(){
            glfwTerminate();
        }
    } glfw_guardian__;

    return unique_ptr<window>(new window_impl(caption, width, height));
}

}