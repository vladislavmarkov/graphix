#pragma once
#ifndef __GFX_MESH_IMPL_HPP__
#define __GFX_MESH_IMPL_HPP__

#include <gfx/glall.hpp>
#include <gfx/mesh.hpp>
#include <gfx/primitive-type.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "vertex-array-object-counter.hpp"

namespace gfx{

class mesh_impl: public mesh{
    const std::string name_;
    std::vector<glm::vec3> vertices_;
    std::vector<unsigned int> faces_;
    primitive_type pri_type_{primitive_type::point};
    GLuint vao_{0};

    bool inited_{false};

    GLuint elementbuffer_;
    GLuint buffer_;

public:
    mesh_impl(
        const std::string &name,
        const std::vector<glm::vec3> &vertices = std::vector<glm::vec3>(),
        const std::vector<unsigned int> &faces = std::vector<unsigned int>()
    ):
        name_(name),
        vertices_(vertices),
        faces_(faces)
    {}

    ~mesh_impl() override{
        glDeleteBuffers(1, &buffer_);
        glDeleteBuffers(1, &elementbuffer_);
        glDeleteVertexArrays(1, &vao_);
    }

    void set_primitive_type(primitive_type type){
        pri_type_ = type;
    }

    std::string name() const override{
        return name_;
    }

    bool init(){
        glGenBuffers(1, &buffer_);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_);
        glBufferData(
            GL_ARRAY_BUFFER,
            vertices_.size() * sizeof(glm::vec3),
            &vertices_[0],
            GL_STATIC_DRAW
        );

        glGenBuffers(1, &elementbuffer_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            faces_.size() * sizeof(unsigned int),
            &faces_[0],
            GL_STATIC_DRAW
        );

        vao_ = get_vertex_count();

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glDisableVertexAttribArray(0);

        return true;
    }

    void draw() override{
        if (!inited_) inited_ = init();

        glBindVertexArray(vao_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_);
        glEnableVertexAttribArray(0);

        glDrawElements(
            GL_POINTS, // static_cast<GLenum>(pri_type_),
            static_cast<int>(faces_.size()),
            GL_UNSIGNED_INT,
            0
        );

        glDisableVertexAttribArray(0);
    }
};

}

#endif // __GFX_MESH_IMPL_HPP__
