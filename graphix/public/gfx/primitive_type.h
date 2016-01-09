#pragma once
#ifndef __GFX_PRIMITIVE_TYPE_H__
#define __GFX_PRIMITIVE_TYPE_H__

#include <gfx/glall.h>

namespace gfx{

enum class primitive_type: unsigned int{
    point = GL_POINTS,
    line = GL_LINES,
    triangle = GL_TRIANGLES,
    polygon = GL_POLYGON
};

}

#endif // __GFX_PRIMITIVE_TYPE_H__
