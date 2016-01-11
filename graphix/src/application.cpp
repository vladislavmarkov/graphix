#include <atomic>
#include <future>
#include <gfx/application.h>
#include <gfx/glall.h>
#include <gfx/window.h>
#include <sstream>
#include <thread>

#include "exception.h"
#include "window_impl.h"

using std::atomic;
using std::invalid_argument;
using std::memory_order_relaxed;
using std::promise;
using std::ref;
using std::runtime_error;
using std::stringstream;
using std::thread;

namespace gfx{

namespace { // anonymous

void glfw3_error_callback(int errcode, const char *description){
    stringstream errmsg;
    errmsg << "err. code: " << errcode << ", err. message: " << description;
    throw glfw3_error(errmsg.str().c_str());
}

} // anonymous

int run(window &main_window){
    window_impl &main_window_impl =
        dynamic_cast<window_impl&>(main_window);

    atomic<bool> done{false};
    std::promise<void> init_callback_promise;

    thread drawing_thread(
        [](
            window_impl &mw_impl,
            atomic<bool> &done,
            promise<void> &init_callback_promise
        ){
            glfwMakeContextCurrent(mw_impl.get_handle());

            glfwSetErrorCallback(glfw3_error_callback);

            glewExperimental = GL_TRUE;
            if (GLEW_OK != glewInit()){
                throw glew_error("failed to initialize glew");
            }

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glDepthFunc(GL_LESS);

            glfwSwapInterval(1);

            mw_impl.init_callbacks();

            init_callback_promise.set_value();

            while (!done.load(memory_order_relaxed)){
                mw_impl.make_frame();
                mw_impl.resize();
                mw_impl.draw();
                mw_impl.swap_buffers();
            }
        },
        ref(main_window_impl),
        ref(done),
        ref(init_callback_promise)
    );

    init_callback_promise.get_future().wait();

    while (!glfwWindowShouldClose(main_window_impl.get_handle())){
        glfwWaitEvents();
    }

    done.store(true, memory_order_relaxed);

    if (drawing_thread.joinable()){
        drawing_thread.join();
    }

    return 0;
}

}
