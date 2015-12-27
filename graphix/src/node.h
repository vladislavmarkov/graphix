#pragma once
#ifndef __GFX_NODE_H__
#define __GFX_NODE_H__

#include <memory>
#include <vector>

struct aiNode;

namespace gfx{

class mesh;

class node{
    node *parent_;
    std::string name_;
    std::vector<std::shared_ptr<node>> children_;
    std::vector<unsigned int> mesh_indices_;
    glm::mat4 transformation_;

public:
    node(node* parent, const std::string &name):
        parent_(parent),
        name_(name)
    {}

    void set_transformation(glm::mat4 t){
        transformation_ = std::move(t);
    }

    void add_mesh_index(unsigned int m){
        mesh_indices_.push_back(m);
    }

    void add_child(std::shared_ptr<node> n){
        children_.emplace_back(n);
    }
};

}

#endif // __GFX_NODE_H__
