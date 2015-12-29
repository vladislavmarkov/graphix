#pragma once
#ifndef __GFX_CAMERA_IMPL_H__
#define __GFX_CAMERA_IMPL_H__

#include <atomic>
#include <gfx/camera.h>
#include <glm/glm.hpp>

namespace gfx{

class camera_impl: public camera{
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 up_vector_;

    mutable std::atomic<bool> modified_{true};

public:
    camera_impl(
        const glm::vec3 &position,
        const glm::vec3 &direction,
        const glm::vec3 up_vector
    ):
        position_(position),
        direction_(direction),
        up_vector_(up_vector)
    {}

    void set_position(const glm::vec3 &position) override{
        position_ = position;
        modified_.store(true, std::memory_order_relaxed);
    }

    glm::vec3 get_position() const override{
        return position_;
    }

    void set_direction(const glm::vec3 &direction) override{
        direction_ = direction;
        modified_.store(true, std::memory_order_relaxed);
    }

    glm::vec3 get_direction() const override{
        return direction_;
    }

    void set_up_vector(const glm::vec3 &up_vector) override{
        up_vector_ = up_vector;
        modified_.store(true, std::memory_order_relaxed);
    }

    glm::vec3 get_up_vector() const override{
        return up_vector_;
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
