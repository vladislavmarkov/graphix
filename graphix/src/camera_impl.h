#pragma once
#ifndef __GFX_CAMERA_IMPL_H__
#define __GFX_CAMERA_IMPL_H__

#include <atomic>
#include <gfx/camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        #ifdef GLM_LEFT_HANDED
            return glm::vec3(mx_[0][2], mx_[1][2], mx_[2][2]);
        #else // GLM_LEFT_HANDED
            return glm::vec3(-mx_[0][2], -mx_[1][2], -mx_[2][2]);
        #endif // GLM_LEFT_HANDED
    }

    glm::vec3 get_down() const override{
        return -get_up();
    }

    glm::vec3 get_forward() const override{
        return -get_backward();
    }

    glm::vec3 get_left() const override{
        return -get_right();
    }

    glm::vec3 get_position() const override{
        glm::mat4 mx_t_ = transpose(mx_);

        // get plane normals
        glm::vec3 n1(mx_t_[0]);
        glm::vec3 n2(mx_t_[1]);
        glm::vec3 n3(mx_t_[2]);

        // get plane distances
        float d1(mx_t_[0].w);
        float d2(mx_t_[1].w);
        float d3(mx_t_[2].w);

        // get the intersection of these 3 planes
        glm::vec3 n2n3 = glm::cross(n2, n3);
        glm::vec3 n3n1 = glm::cross(n3, n1);
        glm::vec3 n1n2 = glm::cross(n1, n2);

        glm::vec3 top = (n2n3 * d1) + (n3n1 * d2) + (n1n2 * d3);
        float denom = glm::dot(n1, n2n3);

        return top / -denom;
    }

    glm::vec3 get_right() const override{
        #ifdef GLM_LEFT_HANDED
            return glm::vec3(mx_[0][0], mx_[1][0], mx_[2][0]);
        #else // GLM_LEFT_HANDED
            return -glm::vec3(mx_[0][0], mx_[1][0], mx_[2][0]);
        #endif // GLM_LEFT_HANDED
    }

    glm::vec3 get_up() const override{
        return glm::vec3(mx_[0][1], mx_[1][1], mx_[2][1]);
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
