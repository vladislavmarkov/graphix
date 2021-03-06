#pragma once
#ifndef __GFX_SCENE_HPP__
#define __GFX_SCENE_HPP__

#include <gfx/camera.hpp>
#include <gfx/drawable.hpp>
#include <gfx/movement.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace gfx{

struct node;

class scene{
    virtual void draw() = 0;

    friend class window_impl;

public:
    virtual ~scene() = default;

    virtual void add(
        std::shared_ptr<node> n,
        std::shared_ptr<drawable> d,
        const std::string &parent = std::string()
    ) = 0;

    virtual void add(std::shared_ptr<movement> m) = 0;

    virtual void make_frame() = 0;
    virtual void request_redraw() = 0;
    virtual void resize(int, int) = 0;
    virtual void set_camera(std::shared_ptr<camera> cam) = 0;
    virtual std::shared_ptr<camera> get_camera() = 0;

    static std::shared_ptr<scene> create(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        std::shared_ptr<camera> cam,
        glm::vec4 clear_color
    );

    static std::shared_ptr<scene> load(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        std::shared_ptr<camera> cam,
        glm::vec4 clear_color,
        const std::string &filename
    );
};

}

#endif // __GFX_SCENE_HPP__
