#include <gfx/primitive_type.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "vertex_array_impl.h"
#include "vertex_array_object_counter.h"

using std::string;
using std::vector;

namespace gfx{

vertex_array_impl::vertex_array_impl(
    const string &name,
    vector<glm::vec3> vertices,
    vector<unsigned int> indices,
    primitive_type type
):
    name_(name),
    vertices_(std::move(vertices)),
    indices_(std::move(indices)),
    pri_type_(type)
{}

vertex_array_impl::~vertex_array_impl(){
    glDeleteBuffers(1, &buffer_);
    glDeleteVertexArrays(1, &vao_);
}

bool vertex_array_impl::init(){
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
        indices_.size() * sizeof(unsigned int),
        &indices_[0],
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

string vertex_array_impl::name() const{
    return name_;
}

void vertex_array_impl::draw(){
    if (!inited_) inited_ = init();

    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_);
    glEnableVertexAttribArray(0);

    glDrawElements(
        static_cast<GLenum>(pri_type_),
        static_cast<int>(indices_.size()),
        GL_UNSIGNED_INT,
        0
    );

    glDisableVertexAttribArray(0);
}

}
