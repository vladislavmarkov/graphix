#include <gfx/window.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>

#include "window_impl.h"

using std::invalid_argument;
using std::unique_ptr;

namespace gfx{

namespace {

enum: size_t {
    default_width = 640,
    default_height = 480
};

}

unique_ptr<window> window::create(
    const std::string &caption,
    size_t width,
    size_t height
){
    if (caption.empty()){
        throw invalid_argument("empty caption");
    }

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

    return unique_ptr<window>(
        new window_impl(
            caption,
            !width ? default_width : width,
            !height ? default_height : height
        )
    );
}

}
