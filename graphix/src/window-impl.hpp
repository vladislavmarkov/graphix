#include <algorithm>
#include <atomic>
#include <gfx/glall.hpp>
#include <gfx/key.hpp>
#include <gfx/scene.hpp>
#include <gfx/window.hpp>
#include <list>
#include <stdexcept>

#include "scene-impl.hpp"

namespace gfx{

class window_impl: public window{
    window_impl(const window_impl&) = delete;
    window_impl &operator = (const window_impl&) = delete;

    GLFWwindow *handle_; // glfw3 handle

    std::string caption_;

    int width_, height_;

    // user context, used by user callback functions
    struct user_context{
        window_impl *wnd_impl_{nullptr};
        window *wnd_{nullptr};

        std::function<
            void(window&, key::code, key::state)
        > *key_func_{nullptr};

        std::function<
            void(window&, double, double)
        > *mouse_move_func_{nullptr};

        std::function<void(window&, int, int)> *resize_func_{nullptr};

        std::function<void(window&)> *draw_func_{nullptr};
    } user_context_;

    std::list<std::weak_ptr<scene>> scenes_;

    std::atomic<bool> redraw_requested_{true};
    std::atomic<bool> resize_requested_{true};

public:
    window_impl(
        const std::string &caption,
        int width,
        int height
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

    void init_callbacks(){
        user_context_.wnd_ = this;
        user_context_.wnd_impl_ = this;

        glfwSetWindowUserPointer(handle_, &user_context_);

        glfwSetFramebufferSizeCallback(handle_, glfw_framebuffer_size_callback);
        glfwSetWindowRefreshCallback(handle_, glfw_refresh_callback);
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

    void set_width(int width) override{
        width_ = width;
    }

    void set_height(int height) override{
        height_ = height;
    }

    std::string get_caption() const override{
        return caption_;
    }

    int get_width() const override{
        return width_;
    }

    int get_height() const override{
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
        if (!user_context_.wnd_){
            user_context_.wnd_ = this;
            user_context_.wnd_impl_ = this;
        }

        user_context_.key_func_ = const_cast<
            std::function<
                void(window&, key::code, key::state)
            >*
        >(&key_func);

        glfwSetWindowUserPointer(handle_, &user_context_);
        glfwSetKeyCallback(handle_, glfw_key_callback);
    }

    static void glfw_mouse_move_callback(GLFWwindow* handle, double x, double y){
        user_context *uc = reinterpret_cast<user_context*>(
            glfwGetWindowUserPointer(handle)
        );

        if (uc && uc->wnd_ && uc->mouse_move_func_){
            (*uc->mouse_move_func_)(*uc->wnd_, x, y);
        }
    }

    void set_mouse_move_reaction(
        const std::function<void(window &wnd, double, double)> &mouse_move_func
    ) override{
        if (!user_context_.wnd_){
            user_context_.wnd_ = this;
            user_context_.wnd_impl_ = this;
        }

        user_context_.mouse_move_func_ = const_cast<
            std::function<void(window&, double, double)>*
        >(&mouse_move_func);

        glfwSetWindowUserPointer(handle_, &user_context_);
        glfwSetCursorPosCallback(handle_, glfw_mouse_move_callback);
    }

    static void glfw_framebuffer_size_callback(
        GLFWwindow* handle,
        int width,
        int height
    ){
        user_context *uc = reinterpret_cast<user_context*>(
            glfwGetWindowUserPointer(handle)
        );

        if (uc && uc->wnd_ && uc->wnd_impl_){
            uc->wnd_impl_->width_ = width;
            uc->wnd_impl_->height_ = height;
            uc->wnd_impl_->resize_requested_.store(
                true, std::memory_order_relaxed
            );

            if (uc->resize_func_){
                (*uc->resize_func_)(*uc->wnd_, width, height);
            }
        }
    }

    void set_resize_reaction(
        const std::function<void(window&, int, int)> &resize_func
    ) override{
        if (!user_context_.wnd_){
            user_context_.wnd_ = this;
            user_context_.wnd_impl_ = this;
        }

        user_context_.resize_func_ = const_cast<
            std::function<
                void(window&, int, int)
            >*
        >(&resize_func);

        glfwSetFramebufferSizeCallback(handle_, glfw_framebuffer_size_callback);
    }

    static void glfw_refresh_callback(GLFWwindow *handle){
        user_context *uc = reinterpret_cast<user_context*>(
            glfwGetWindowUserPointer(handle)
        );

        if (uc && uc->wnd_ && uc->wnd_impl_){
            if (uc->draw_func_){
                (*uc->draw_func_)(*uc->wnd_);
            }

            uc->wnd_impl_->request_redraw();
        }
    }

    void set_refresh_reaction(
        const std::function<void(window&)> &draw_func
    ) override{
        if (!user_context_.wnd_){
            user_context_.wnd_ = this;
            user_context_.wnd_impl_ = this;
        }

        user_context_.draw_func_ = const_cast<
            std::function<void(window&)>*
        >(&draw_func);

        glfwSetWindowRefreshCallback(handle_, glfw_refresh_callback);
    }

    void add(std::shared_ptr<scene> scene_obj) override{
        if (scene_obj){
            scene_impl *pimpl = dynamic_cast<scene_impl*>(scene_obj.get());
            if (pimpl) pimpl->parent_ = this;
            scenes_.push_back(scene_obj);
        }
    }

    void disable_mouse_cursor() const override{
        glfwSetInputMode(handle_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void enable_mouse_cursor() const override{
        show_mouse_cursor();
    }

    void hide_mouse_cursor() const override{
        glfwSetInputMode(handle_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void show_mouse_cursor() const override{
        glfwSetInputMode(handle_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    key::state get_key(key::code kc) const override{
        return static_cast<key::state>(
            glfwGetKey(handle_, static_cast<int>(kc))
        );
    }

    void get_cursor_pos(double &x, double &y) const override{
        glfwGetCursorPos(handle_, &x, &y);
    }

    void resize(){
        if (!resize_requested_.load(std::memory_order_relaxed)) return;

        std::for_each(std::begin(scenes_), std::end(scenes_),
            [this](std::weak_ptr<scene> &scene_obj){
                std::shared_ptr<scene> s = scene_obj.lock();
                if (s) s->resize(width_, height_);
            }
        );

        resize_requested_.store(false, std::memory_order_relaxed);

        request_redraw();
    }

    void draw(){
        if (!redraw_requested_.load(std::memory_order_relaxed)) return;

        std::for_each(std::begin(scenes_), std::end(scenes_),
            [](std::weak_ptr<scene> &scene_obj){
                std::shared_ptr<scene> s = scene_obj.lock();
                if (s) s->draw();
            }
        );
    }

    void make_frame(){
        std::for_each(std::begin(scenes_), std::end(scenes_),
            [](std::weak_ptr<scene> &scene_obj){
                std::shared_ptr<scene> s = scene_obj.lock();
                if (s) s->make_frame();
            }
        );
    }

    void request_redraw(){
        redraw_requested_.store(true, std::memory_order_relaxed);
    }

    void swap_buffers(){
        if (redraw_requested_.load(std::memory_order_relaxed)){
            glfwSwapBuffers(handle_);
            redraw_requested_.store(false, std::memory_order_relaxed);
        }
    }
};

}
