#include <gfx/glall.hpp>
#include <gfx/window.hpp>
#include <memory>
#include <stdexcept>

#include "window-impl.hpp"
#include "exception.hpp"

using std::invalid_argument;
using std::shared_ptr;

namespace gfx{

namespace {

enum: int {
    default_width = 640,
    default_height = 480
};

}

shared_ptr<window> window::create(
    const std::string &caption,
    int width,
    int height
){
    if (caption.empty()){
        throw invalid_argument("empty caption");
    }

    static struct guardian__{
        guardian__(){
            if (!glfwInit()){
                glfwTerminate();
                throw glfw3_error("failed to initialize glfw");
            }

            glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        ~guardian__(){
            glfwTerminate();
        }
    } glfw_guardian__;

    return shared_ptr<window>(
        new window_impl(
            caption,
            !width ? default_width : width,
            !height ? default_height : height
        )
    );
}

}
