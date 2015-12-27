#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <atomic>
#include <gfx/key.h>
#include <gfx/scene.h>
#include <gfx/window.h>
#include <list>
#include <stdexcept>

#include "scene_impl.h"

namespace gfx{

class window_impl: public window{
    GLFWwindow *handle_; // glfw3 handle

    std::string caption_;

    int width_, height_;

    // user context, used by user callback functions
    struct user_context{
        window_impl *wnd_impl_{nullptr};
        window *wnd_{nullptr};

        std::function<
            void(window &wnd, key::code, key::state)
        > *key_func_{nullptr};

        std::function<void(window &wnd, int, int)> *resize_func_{nullptr};

        std::function<void(window&)> *draw_func_{nullptr};
    } user_context_;

    std::list<scene_impl*> scenes_;

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

        if (uc && uc->wnd_ && uc->wnd_impl_){
            uc->wnd_impl_->resize(width, height);

            if (uc->resize_func_){
                (*uc->resize_func_)(*uc->wnd_, width, height);
            }
        }
    }

    void set_resize_reaction(
        const std::function<void(window&, int, int)> &resize_func
    ) override{
        user_context_.wnd_ = this;
        user_context_.wnd_impl_ = this;
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
            uc->wnd_impl_->draw();

            if (uc->draw_func_){
                (*uc->draw_func_)(*uc->wnd_);
            }
        }
    }

    void set_refresh_reaction(
        const std::function<void(window&)> &draw_func
    ) override{
        user_context_.wnd_ = this;
        user_context_.wnd_impl_ = this;
        user_context_.draw_func_ = const_cast<
            std::function<void(window&)>*
        >(&draw_func);

        glfwSetWindowRefreshCallback(handle_, glfw_refresh_callback);
    }

    void add(scene *scene_obj) override{
        scenes_.push_back(dynamic_cast<scene_impl*>(scene_obj));
    }

    void resize(int width, int height){
        std::for_each(std::begin(scenes_), std::end(scenes_),
            [&width, &height](scene_impl *scene_obj){
                if (scene_obj){
                    scene_obj->resize(width, height);
                }
            }
        );
    }

    void draw(){
        std::for_each(std::begin(scenes_), std::end(scenes_),
            [](scene_impl *scene_obj){
                if (scene_obj){
                    scene_obj->draw();
                }
            }
        );
    }
};

}
