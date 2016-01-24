#pragma once
#ifndef __GFX_PRIMITIVE_TYPE_HPP__
#define __GFX_PRIMITIVE_TYPE_HPP__

#include <gfx/glall.hpp>

namespace gfx{

enum class primitive_type: unsigned int{
    point = GL_POINTS,
    line = GL_LINES,
    triangle = GL_TRIANGLES,
    polygon = GL_POLYGON
};

}

#endif // __GFX_PRIMITIVE_TYPE_HPP__
