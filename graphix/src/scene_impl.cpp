#include <algorithm>
#include <gfx/movement.h>
#include <gfx/node.h>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <stack>

#include "movement_impl.h"
#include "scene_impl.h"
#include "window_impl.h"

using std::begin; using std::end;
using std::invalid_argument;
using std::memory_order_relaxed;
using std::shared_ptr;
using std::stack;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

namespace gfx{

void scene_impl::instantiate_shaders_if_required_(){
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
        program_ = unique_ptr<shader_program>(new shader_program());
        relink_required = true;
    }

    if (relink_required){
        program_->attach(vshdr_);
        program_->attach(fshdr_);
        program_->link();
        program_->use();
    }
}

void scene_impl::init_dependencies(){
    nodep_geometrics_.add_dependency(&dep_projection_);
    nodep_camera_.add_dependency(&dep_mvp_);
    dep_projection_.add_dependency(&dep_mvp_);

    // update everything in a dependency tree
    nodep_geometrics_.set(hfov_, size_, depth_);
    nodep_camera_.set(active_camera_);
}

void scene_impl::draw(){
    if (!active_camera_){
        throw std::logic_error("no active camera is set");
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(
        clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w
    );

    instantiate_shaders_if_required_();

    if (active_camera_->was_moved()){
        nodep_camera_.update();
    }

    stack<node*> nodes;
    nodes.push(root_.get());
    while (!nodes.empty()){
        node *current = nodes.top();
        nodes.pop();
        if (!current) continue;
        dep_mvp_.set(
            projection_ *
            active_camera_->get_matrix() *
            current->transformation_
        );

        program_->use();
        GLuint mvp_handle = glGetUniformLocation(program_->handle(), "mvp");
        glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, glm::value_ptr(mvp_));
        for_each(
            begin(current->drawable_indices_),
            end(current->drawable_indices_),
            [this](unsigned int idx){
                if (drawables_[idx]) drawables_[idx]->draw();
            }
        );

        for_each(
            begin(current->children_),
            end(current->children_),
            [&nodes](shared_ptr<node> &n){
                if (n) nodes.push(n.get());
            }
        );
    }
}

scene_impl::scene_impl(
    float hfov,
    int width,
    int height,
    float near,
    float far,
    camera *cam,
    glm::vec4 clear_color
):
    vshdr_(nullptr), fshdr_(nullptr), root_(new node(nullptr, "root")),
    hfov_(hfov), size_{width, height}, depth_{near, far},
    nodep_geometrics_(&hfov_, &size_, &depth_),
    projection_(1.0f),
    dep_projection_(&projection_, &hfov_, &size_, &depth_),
    active_camera_(cam), nodep_camera_(active_camera_),
    mvp_(1.0f), dep_mvp_(&mvp_, &projection_, active_camera_),
    clear_color_(clear_color)
{
    init_dependencies();
}

scene_impl::scene_impl(
    float hfov,
    int width,
    int height,
    float near,
    float far,
    camera *cam,
    glm::vec4 clear_color,
    shared_ptr<node> &&root,
    vector<shared_ptr<drawable>> &&drawables
):
    vshdr_(nullptr), fshdr_(nullptr),
    root_(std::move(root)), drawables_(std::move(drawables)),
    hfov_(hfov), size_{width, height}, depth_{near, far},
    nodep_geometrics_(&hfov_, &size_, &depth_),
    projection_(1.0f),
    dep_projection_(&projection_, &hfov_, &size_, &depth_),
    active_camera_(cam), nodep_camera_(active_camera_),
    mvp_(1.0f), dep_mvp_(&mvp_, &projection_, active_camera_),
    clear_color_(clear_color)
{
    init_dependencies();
}

void scene_impl::add(
    shared_ptr<node> n,
    shared_ptr<drawable> d,
    const string &parent
){
    if (!n || !d){
        throw invalid_argument("null pointers are not acceptable");
    }

    drawables_.push_back(d);
    n->drawable_indices_.push_back(
        static_cast<unsigned int>(drawables_.size() - 1)
    );

    if (parent.empty()){
        root_->children_.push_back(n);
    }else{
        auto pnode = find_node(root_, parent);
        if (!pnode){
            stringstream errmsg;
            errmsg << "there is no node with name \"" << parent << "\"";
            throw invalid_argument(errmsg.str());
        }

        pnode->children_.push_back(n);
    }
}

void scene_impl::add(shared_ptr<movement> m){
    movements_.emplace_back(std::move(m));
}

void scene_impl::make_frame(){
    for_each(begin(movements_), end(movements_),
        [](shared_ptr<movement> elem){
            elem->make_move();
        }
    );
}

void scene_impl::request_redraw(){
    if (parent_){
        parent_->request_redraw();
    }
}

void scene_impl::resize(int width, int height){
    nodep_geometrics_.set(size{width, height});
}

void scene_impl::set_camera(camera *cam){
    nodep_camera_.set(cam);
}

camera *scene_impl::get_camera(){
    return active_camera_;
}

}
