#pragma once
#ifndef __GFX_VERTEX_ARRAY_HPP__
#define __GFX_VERTEX_ARRAY_HPP__

#include <gfx/drawable.hpp>
#include <gfx/primitive-type.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace gfx{

class vertex_array: public drawable{
public:
    static std::shared_ptr<drawable> create(
        const std::string &name,
        std::vector<glm::vec3> vertices,
        std::vector<unsigned int> indices,
        primitive_type type
    );
};

}

#endif // __GFX_VERTEX_ARRAY_HPP__
