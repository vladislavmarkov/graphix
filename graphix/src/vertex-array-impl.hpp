#pragma once
#ifndef __GFX_VERTEX_ARRAY_IMPL_HPP__
#define __GFX_VERTEX_ARRAY_IMPL_HPP__

#include <gfx/primitive-type.hpp>
#include <gfx/vertex-array.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace gfx{

class vertex_array_impl: public vertex_array{
    const std::string name_;
    std::vector<glm::vec3> vertices_;
    std::vector<unsigned int> indices_;
    primitive_type pri_type_{primitive_type::point};
    GLuint vao_{0};

    bool inited_{false};

    GLuint elementbuffer_;
    GLuint buffer_;

public:
    vertex_array_impl(
        const std::string &name,
        std::vector<glm::vec3> vertices,
        std::vector<unsigned int> indices,
        primitive_type type
    );

    ~vertex_array_impl();

    bool init();

    std::string name() const override;

    void draw() override;
};

}

#endif // __GFX_VERTEX_ARRAY_IMPL_HPP__
