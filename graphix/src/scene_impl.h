#pragma once
#ifndef __GFX_SCENE_IMPL_H__
#define __GFX_SCENE_IMPL_H__

#include <algorithm>
#include <atomic>
#include <gfx/scene.h>
#include <gfx/volumetric.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <stdexcept>

#include "dependent.h"

namespace gfx{

class scene_impl: public scene{
    std::list<volumetric*> volumetrics_;
    std::atomic<bool> modified_{true};

    float hfov_;

    class nodep_hfov: public dependent{
        float *hfov_;

    public:
        nodep_hfov(float *ptr): hfov_(ptr){}

        void adjust() override{ /* do nothing */ }

        void set(float value){
            if (hfov_) *hfov_ = value;
            update();
        }
    } nodep_hfov_;

    struct size{
        int width_;
        int height_;
    } size_;

    class nodep_size: public dependent{
        size *size_;

    public:
        nodep_size(size *ptr): size_(ptr){}

        void adjust() override{ /* do nothing */ }

        void set(int width, int height){
            if (size_){
                size_->width_ = width;
                size_->height_ = height;
                update();
            }
        }
    } nodep_size_;

    struct depth{
        float near_;
        float far_;
    } depth_;

    class nodep_depth: public dependent{
        depth *depth_;

    public:
        nodep_depth(depth *ptr): depth_(ptr){}

        void adjust() override{ /* do nothing */ }

        void set(float near, float far){
            if (depth_){
                depth_->near_ = near;
                depth_->far_ = far;
                update();
            }
        }
    } nodep_depth_;

    glm::mat4 projection_;

    class dep_projection: public dependent{
        glm::mat4 *projection_;
        float *hfov_;
        size *size_;
        depth *depth_;

    public:
        dep_projection(glm::mat4 *projection, float *hfov, size *wh, depth *nf):
            projection_(projection),
            hfov_(hfov),
            size_(wh),
            depth_(nf)
        {}

        void adjust() override{
            if (projection_ && hfov_ && size_ && depth_){
                *projection_ = glm::perspective(
                    glm::radians(*hfov_),
                    static_cast<float>(size_->width_) /
                    static_cast<float>(size_->height_),
                    depth_->near_, depth_->far_
                );
            }
        }
    } dep_projection_;

    camera* active_camera_{nullptr};

    class nodep_camera: public dependent{
        camera *camera_;

    public:
        nodep_camera(camera *cam): camera_(cam){}

        void adjust() override{ /* do nothing */ }

        void set(camera *cam){
            camera_ = cam;
            update();
        }
    } nodep_camera_;

    glm::mat4 view_;

    class dep_view: public dependent{
        glm::mat4 *view_;
        camera *camera_;

    public:
        dep_view(glm::mat4 *view, camera *cam):
            view_(view),
            camera_(cam)
        {}

        void adjust() override{
            if (view_ && camera_){
                *view_ = glm::lookAt(
                    camera_->get_position(),
                    camera_->get_position() + camera_->get_direction(),
                    camera_->get_up_vector()
                );
            }
        }
    } dep_view_;

    glm::mat4 mvp_;

    class dep_mvp: public dependent{
        glm::mat4 *mvp_;
        glm::mat4 *projection_;
        glm::mat4 *view_;

    public:
        dep_mvp(glm::mat4 *mvp, glm::mat4 *projection, glm::mat4 *view):
            mvp_(mvp), projection_(projection), view_(view)
        {}

        void adjust() override{
            if (mvp_ && view_ && projection_){
                *mvp_ = *projection_ * *view_;
            }
        }
    } dep_mvp_;

public:
    scene_impl(
        float hfov, int width, int height, float near, float far, camera *cam
    ):
        hfov_(hfov), nodep_hfov_(&hfov_),
        size_{width, height}, nodep_size_(&size_),
        depth_{near, far}, nodep_depth_(&depth_),
        projection_(1.0f),
        dep_projection_(
            &projection_,
            &hfov_,
            &size_,
            &depth_
        ),
        active_camera_(cam), nodep_camera_(active_camera_),
        view_(1.0f), dep_view_(&view_, cam),
        mvp_(1.0f), dep_mvp_(&mvp_, &projection_, &view_)
    {}

    void add(volumetric *vol) override{
        volumetrics_.push_back(vol);
        modified_.store(true, std::memory_order_relaxed);
    }

    void set_camera(camera *cam){
        active_camera_ = cam;
        modified_.store(true, std::memory_order_relaxed);
    }

    void draw() override{
        if (!active_camera_){
            throw std::logic_error("no active camera is set");
        }

        std::for_each(std::begin(volumetrics_), std::end(volumetrics_),
            [](volumetric *vol){
                if (vol) vol->draw();
            }
        );

        modified_.store(false, std::memory_order_relaxed);
    }
};

}

#endif // __GFX_SCENE_IMPL_H__
