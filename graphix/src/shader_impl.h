#pragma once
#ifndef __GFX_SHADER_IMPL_H__
#define __GFX_SHADER_IMPL_H__

#include <gfx/shader.h>

namespace gfx{

class shader_impl: public shader{
    const shader::type type_;
    const std::string code_;

public:
    shader_impl(shader::type t, const std::string &code):
        type_(t),
        code_(code)
    {}
};

}

#endif // __GFX_SHADER_IMPL_H__
