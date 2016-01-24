#pragma once
#ifndef __GFX_CAMERA_HPP__
#define __GFX_CAMERA_HPP__

#include <glm/glm.hpp>
#include <memory>

namespace gfx{

class camera{
public:
    virtual glm::mat4 get_matrix() const = 0;
    virtual glm::vec3 get_backward() const = 0;
    virtual glm::vec3 get_down() const = 0;
    virtual glm::vec3 get_forward() const = 0;
    virtual glm::vec3 get_left() const = 0;
    virtual glm::vec3 get_position() const = 0;
    virtual glm::vec3 get_right() const = 0;
    virtual glm::vec3 get_up() const = 0;
    virtual void set_matrix(glm::mat4 m) = 0;

    virtual void shot() const = 0;
    virtual bool was_moved() const = 0;

    static std::shared_ptr<camera> create(glm::mat4 mx);
};

}

#endif // __GFX_CAMERA_HPP__
