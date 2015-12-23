#pragma once
#ifndef __GFX_SHADER_H__
#define __GFX_SHADER_H__

#include <gfx/glall.h>
#include <memory>
#include <type_traits>

namespace gfx{

enum class shader_type: GLenum{
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER
};

template<shader_type T>
class shader{
    static_assert(
        T == shader_type::vertex || T == shader_type::fragment,
        "invalid type of shader"
    );

public:
    virtual ~shader() = default;

    static std::unique_ptr<shader> create(const std::string &code);
    static std::unique_ptr<shader> load_from_file(const std::string &filename);
    static std::unique_ptr<shader> create_default();
};

}

#endif // __GFX_SHADER_H__
