#include <atomic>
#include <gfx/key.h>
#include <gfx/window.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace gfx{

class window_impl: public window{
    GLFWwindow *handle_; // glfw3 handle

    std::string caption_;

    size_t
        width_,
        height_;

    // modification flag (if true, then window should be redrawn)
    std::atomic<bool> content_modified_{true};

    // user context, used by user callback functions
    struct user_context{
        window *wnd_;

        std::function<
            void(window &wnd, key::code, key::state)
        > *key_func_;

        std::function<
            void(window &wnd, int, int)
        > *resize_func_;
    } user_context_;

public:
    window_impl(
        const std::string &caption,
        size_t width,
        size_t height
    ):
        handle_(
            glfwCreateWindow(
                static_cast<int>(width), static_cast<int>(height),
                caption.c_str(), nullptr, nullptr
            )
        ),
        caption_(caption),
        width_(width),
        height_(height)
    {
        if (!handle_){
            throw std::runtime_error("failed to create window");
        }
    }

    ~window_impl() override{
        glfwDestroyWindow(handle_);
    }

    const GLFWwindow* get_handle() const{
        return handle_;
    }

    GLFWwindow* get_handle(){
        return const_cast<GLFWwindow*>(
            const_cast<const window_impl&>(*this).get_handle()
        );
    }

    void set_caption(const std::string &caption) override{
        caption_ = caption;
    }

    void set_width(size_t width) override{
        width_ = width;
    }

    void set_height(size_t height) override{
        height_ = height;
    }

    std::string get_caption() const override{
        return caption_;
    }

    size_t get_width() const override{
        return width_;
    }

    size_t get_height() const override{
        return height_;
    }

    void close() override{
        glfwSetWindowShouldClose(handle_, GL_TRUE);
    }

    static void glfw_key_callback(
        GLFWwindow* handle,
        int key,
        int /*scancode*/,
        int action,
        int /*mods*/
    ){
        user_context *uc = reinterpret_cast<user_context*>(
            glfwGetWindowUserPointer(handle)
        );

        if (uc && uc->wnd_ && uc->key_func_){
            (*uc->key_func_)(
                *uc->wnd_,
                static_cast<key::code>(key),
                static_cast<key::state>(action)
            );
        }
    }

    void set_key_reaction(
        const std::function<void(window &wnd, key::code, key::state)> &key_func
    ) override{
        user_context_.wnd_ = this;
        user_context_.key_func_ = const_cast<
            std::function<
                void(window&, key::code, key::state)
            >*
        >(&key_func);

        glfwSetWindowUserPointer(
            handle_,
            &user_context_
        );

        glfwSetKeyCallback(handle_, glfw_key_callback);
    }

    static void glfw_framebuffer_size_callback(
        GLFWwindow* handle,
        int width,
        int height
    ){
        user_context *uc = reinterpret_cast<user_context*>(
            glfwGetWindowUserPointer(handle)
        );

        if (uc && uc->wnd_){
            if (uc->resize_func_){
                (*uc->resize_func_)(*uc->wnd_, width, height);
            }

            (dynamic_cast<window_impl*>(uc->wnd_))->content_modified_
                .store(true, std::memory_order_relaxed);
        }
    }

    void set_resize_reaction(
        const std::function<void(window &wnd, int, int)> &resize_func
    ) override{
        user_context_.wnd_ = this;
        user_context_.resize_func_ = const_cast<
            std::function<
                void(window&, int, int)
            >*
        >(&resize_func);
    }

    void draw(){
        // TODO: drawing routine

        content_modified_.store(false, std::memory_order_relaxed);
    }

    bool content_modified(){
        return content_modified_.load(std::memory_order_relaxed);
    }
};

}
