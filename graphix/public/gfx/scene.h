#pragma once
#ifndef __GFX_SCENE_H__
#define __GFX_SCENE_H__

#include <gfx/camera.h>
#include <gfx/drawable.h>
#include <gfx/volumetric.h>
#include <glm/glm.hpp>
#include <memory>

namespace gfx{

class scene{
public:
    virtual void add(volumetric *obj) = 0;
    virtual void set_camera(camera *cam) = 0;

    static std::unique_ptr<scene> create(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color
    );
};

}

#endif // __GFX_SCENE_H__
