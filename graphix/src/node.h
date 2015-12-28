#pragma once
#ifndef __GFX_NODE_H__
#define __GFX_NODE_H__

#include <memory>
#include <vector>

struct aiNode;

namespace gfx{

class mesh;

struct node{
    node *parent_;
    std::string name_;
    std::vector<std::shared_ptr<node>> children_;
    std::vector<unsigned int> mesh_indices_;
    glm::mat4 transformation_;

    node(node* parent, const std::string &name):
        parent_(parent),
        name_(name)
    {}
};

}

#endif // __GFX_NODE_H__
