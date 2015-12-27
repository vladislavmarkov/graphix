#pragma once
#ifndef __GFX_SCENE_IMPL_H__
#define __GFX_SCENE_IMPL_H__

#include <algorithm>
#include <atomic>
#include <gfx/glall.h>
#include <gfx/mesh.h>
#include <gfx/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <stdexcept>
#include <vector>

#include "dependent.h"
#include "node.h"
#include "shader_program.h"

namespace gfx{

class scene_impl: public scene{
    std::unique_ptr<shader_program> program_;
    shader<shader_type::vertex> *vshdr_;
    shader<shader_type::fragment> *fshdr_;
    std::unique_ptr<shader<shader_type::vertex>> own_vshdr_;
    std::unique_ptr<shader<shader_type::fragment>> own_fshdr_;

    std::shared_ptr<node> root_;
    std::vector<std::shared_ptr<mesh>> meshes_;
    std::atomic<bool> modified_{true};

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

    glm::vec4 clear_color_;

    void instantiate_shaders_if_required_(){
        bool relink_required = false;

        if (!own_vshdr_){
            own_vshdr_ = shader<shader_type::vertex>::create_default();
            relink_required = true;
        }

        if (!vshdr_){
            vshdr_ = own_vshdr_.get();
            relink_required = true;
        }

        if (!own_fshdr_){
            own_fshdr_ = shader<shader_type::fragment>::create_default();
            relink_required = true;
        }

        if (!fshdr_){
            fshdr_ = own_fshdr_.get();
            relink_required = true;
        }

        if (!program_){
            program_ = std::unique_ptr<shader_program>(new shader_program());
            relink_required = true;
        }

        if (relink_required){
            program_->attach(vshdr_);
            program_->attach(fshdr_);
            program_->link();
            program_->use();
        }
    }

    void init_dependencies(){
        nodep_geometrics_.add_dependency(&dep_projection_);
        nodep_camera_.add_dependency(&dep_view_);
        dep_projection_.add_dependency(&dep_mvp_);
        dep_view_.add_dependency(&dep_mvp_);

        // update everything in a dependency tree
        nodep_geometrics_.set(hfov_, size_, depth_);
        nodep_camera_.set(active_camera_);
    }

public:
    scene_impl(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color
    ):
        vshdr_(nullptr), fshdr_(nullptr),
        hfov_(hfov), size_{width, height}, depth_{near, far},
        nodep_geometrics_(&hfov_, &size_, &depth_),
        projection_(1.0f),
        dep_projection_(&projection_, &hfov_, &size_, &depth_),
        active_camera_(cam), nodep_camera_(active_camera_),
        view_(1.0f), dep_view_(&view_, cam),
        mvp_(1.0f), dep_mvp_(&mvp_, &projection_, &view_),
        clear_color_(clear_color)
    {
        init_dependencies();
    }

    scene_impl(
        float hfov,
        int width,
        int height,
        float near,
        float far,
        camera *cam,
        glm::vec4 clear_color,
        std::shared_ptr<node> root,
        std::vector<std::shared_ptr<mesh>> meshes
    ):
        vshdr_(nullptr), fshdr_(nullptr), root_(root), meshes_(meshes),
        hfov_(hfov), size_{width, height}, depth_{near, far},
        nodep_geometrics_(&hfov_, &size_, &depth_),
        projection_(1.0f),
        dep_projection_(&projection_, &hfov_, &size_, &depth_),
        active_camera_(cam), nodep_camera_(active_camera_),
        view_(1.0f), dep_view_(&view_, cam),
        mvp_(1.0f), dep_mvp_(&mvp_, &projection_, &view_),
        clear_color_(clear_color)
    {
        init_dependencies();
    }

    void add(std::shared_ptr<mesh> obj) override{
        meshes_.push_back(obj);
        modified_.store(true, std::memory_order_relaxed);
    }

    void resize(int width, int height){
        nodep_geometrics_.set(size{width, height});
    }

    void draw(){
        if (!active_camera_){
            throw std::logic_error("no active camera is set");
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(
            clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w
        );

        instantiate_shaders_if_required_();
        program_->use();
        GLuint mvp_handle = glGetUniformLocation(program_->handle(), "mvp");
        glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, glm::value_ptr(mvp_));

        std::for_each(std::begin(meshes_), std::end(meshes_),
            [](std::shared_ptr<mesh> obj){
                if (obj) obj->draw();
            }
        );

        modified_.store(false, std::memory_order_relaxed);
    }

    void set_camera(camera *cam) override{
        active_camera_ = cam;
        modified_.store(true, std::memory_order_relaxed);
    }
};

}

#endif // __GFX_SCENE_IMPL_H__
