#pragma once
#ifndef __GFX_NODE_HPP__
#define __GFX_NODE_HPP__

#include <glm/glm.hpp>
#include <memory>
#include <vector>

struct aiNode;

namespace gfx{

class mesh;

struct node{
    node *parent_;
    std::string name_;
    std::vector<std::shared_ptr<node>> children_;
    std::vector<unsigned int> drawable_indices_;
    glm::mat4 transformation_;

    node(
        node* parent,
        const std::string &name,
        glm::mat4 t = glm::mat4(1.0f)
    ):
        parent_(parent),
        name_(name),
        transformation_(t)
    {}
};

std::shared_ptr<node> find_node(
    std::shared_ptr<node> root,
    const std::string &name
);

}

#endif // __GFX_NODE_HPP__
