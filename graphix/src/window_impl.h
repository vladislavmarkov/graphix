#include <gfx/window.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace gfx{

class window_impl: public window{
    GLFWwindow *glfw_w_;

    std::string caption_;

    size_t
        width_,
        height_;

public:
    window_impl(
        const std::string &caption,
        size_t width,
        size_t height
    ):
        glfw_w_(
            glfwCreateWindow(
                static_cast<int>(width), static_cast<int>(height),
                caption.c_str(), nullptr, nullptr
            )
        ),
        caption_(caption),
        width_(width),
        height_(height)
    {
        if (!glfw_w_){
            throw std::runtime_error("failed to create window");
        }
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
};

}