#pragma once
#ifndef __GFX_SCENE_IMPL_H__
#define __GFX_SCENE_IMPL_H__

#include <atomic>
#include <gfx/movement.h>
#include <gfx/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "dependent.h"
#include "shader_program.h"

namespace gfx{

class window_impl;

class scene_impl: public scene{
    window_impl *parent_{nullptr};
    std::unique_ptr<shader_program> program_;
    shader<shader_type::vertex> *vshdr_;
    shader<shader_type::fragment> *fshdr_;
    std::unique_ptr<shader<shader_type::vertex>> own_vshdr_;
    std::unique_ptr<shader<shader_type::fragment>> own_fshdr_;

    std::shared_ptr<node> root_;
    std::vector<std::shared_ptr<drawable>> drawables_;
    std::vector<std::shared_ptr<movement>> movements_;

    float hfov_;

    struct size{
        int width_;
        int height_;
    } size_;

    struct depth{
        float near_;
        float far_;
    } depth_;

    class nodep_geometrics: public dependent{
        float *hfov_;
        size *size_;
        depth *depth_;

    public:
        nodep_geometrics(float *hfov, size *sz, depth *nf):
            hfov_(hfov), size_(sz), depth_(nf)
        {
            if (size_){
                glViewport(0, 0, size_->width_, size_->height_);
            }
        }

        void adjust() override{ /* do nothing */ }

        void set(float value){
            if (hfov_) *hfov_ = value;
            update();
        }

        void set(size value){
            if (size_){
                *size_ = value;
                glViewport(0, 0, size_->width_, size_->height_);
            }
            update();
        }

        void set(depth value){
            if (depth_) *depth_ = value;
            update();
        }

        void set(float hfov, size sz, depth nf){
            if (hfov_) *hfov_ = hfov;
            if (size_) *size_ = sz;
            if (depth_) *depth_ = nf;
            update();
        }
    } nodep_geometrics_;

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

    glm::mat4 mvp_;

    class dep_mvp: public dependent{
        glm::mat4 *mvp_;
        glm::mat4 *projection_;
        camera *cam_;

    public:
        dep_mvp(glm::mat4 *mvp, glm::mat4 *projection, camera *cam):
            mvp_(mvp), projection_(projection), cam_(cam)
        {}

        void adjust() override{
            if (mvp_ && cam_ && projection_){
                *mvp_ = *projection_ * cam_->get_matrix();
            }
        }

        void set(glm::mat4 mvp){
            *mvp_ = std::move(mvp);
        }
    } dep_mvp_;

    glm::vec4 clear_color_;

    void instantiate_shaders_if_required_();
    void init_dependencies();

    void draw() override;

    friend class window_impl;

public:
    scene_impl(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color
    );

    scene_impl(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color,
        std::shared_ptr<node> &&root,
        std::vector<std::shared_ptr<drawable>> &&drawables
    );

    void add(
        std::shared_ptr<node> n,
        std::shared_ptr<drawable> d,
        const std::string &parent
    ) override;

    void add(std::shared_ptr<movement> m) override;

    void make_frame() override;

    void request_redraw() override;

    void resize(int width, int height) override;

    void set_camera(camera *cam) override;
};

}

#endif // __GFX_SCENE_IMPL_H__
