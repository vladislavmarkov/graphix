#pragma once
#ifndef __GFX_CAMERA_H__
#define __GFX_CAMERA_H__

#include <glm/glm.hpp>
#include <memory>

namespace gfx{

class camera{
public:
    virtual void set_position(const glm::vec3 &position) = 0;
    virtual glm::vec3 get_position() const = 0;

    virtual void set_direction(const glm::vec3 &direction) = 0;
    virtual glm::vec3 get_direction() const = 0;

    virtual void set_up_vector(const glm::vec3 &up) = 0;
    virtual glm::vec3 get_up_vector() const = 0;

    static std::unique_ptr<camera> create(
        const glm::vec3 &position,
        const glm::vec3 &direction,
        const glm::vec3 &up_vector
    );
};

}

#endif // __GFX_CAMERA_H__
