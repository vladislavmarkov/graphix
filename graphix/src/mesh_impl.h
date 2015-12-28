#pragma once
#ifndef __GFX_MESH_IMPL_H__
#define __GFX_MESH_IMPL_H__

#include <gfx/glall.h>
#include <gfx/mesh.h>

// temp
#include <iostream>
// temp

namespace gfx{

class mesh_impl: public mesh{
    const std::string name_;
    std::vector<glm::vec3> vertices_;
    std::vector<unsigned int> faces_;
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

        static GLuint vao_index = 0;
        vao_ = vao_index++;

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_);
        glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        return true;
    }

    void draw() override{
        if (!inited_) init();

        glBindVertexArray(vao_);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(
            GL_POINTS,
            static_cast<int>(faces_.size()),
            GL_UNSIGNED_INT,
            0
        );
    }
};

}

#endif // __GFX_MESH_IMPL_H__
