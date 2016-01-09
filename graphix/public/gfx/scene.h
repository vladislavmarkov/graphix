#pragma once
#ifndef __GFX_SCENE_H__
#define __GFX_SCENE_H__

#include <gfx/camera.h>
#include <gfx/drawable.h>
#include <gfx/movement.h>
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
    virtual void set_camera(camera *cam) = 0;

    static std::shared_ptr<scene> create(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color
    );

    static std::shared_ptr<scene> load(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color,
        const std::string &filename
    );
};

}

#endif // __GFX_SCENE_H__
