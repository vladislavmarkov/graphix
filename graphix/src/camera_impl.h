#pragma once
#ifndef __GFX_CAMERA_IMPL_H__
#define __GFX_CAMERA_IMPL_H__

#include <atomic>
#include <gfx/camera.h>
#include <gfx/matrix-helpers.h>

namespace gfx{

class camera_impl: public camera{
    glm::mat4 mx_;
    mutable std::atomic<bool> modified_{true};

public:
    camera_impl(glm::mat4 mx):
        mx_(std::move(mx))
    {}

    glm::mat4 get_matrix() const{
        return mx_;
    }

    glm::vec3 get_backward() const override{
        return -gfx::get_direction(mx_);
    }

    glm::vec3 get_down() const override{
        return -get_up();
    }

    glm::vec3 get_forward() const override{
        return gfx::get_direction(mx_);
    }

    glm::vec3 get_left() const override{
        return -get_right();
    }

    glm::vec3 get_position() const override{
        return gfx::get_position(mx_);
    }

    glm::vec3 get_right() const override{
        return gfx::get_right(mx_);
    }

    glm::vec3 get_up() const override{
        return gfx::get_up(mx_);
    }

    void set_matrix(glm::mat4 m) override{
        mx_ = std::move(m);
        modified_.store(true, std::memory_order_relaxed);
    }

    void shot() const override{
        modified_.store(false, std::memory_order_relaxed);
    }

    bool was_moved() const override{
        return modified_.load(std::memory_order_relaxed);
    }
};

}

#endif // __GFX_CAMERA_IMPL_H__
