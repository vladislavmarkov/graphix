#pragma once
#ifndef __GFX_SHADER_IMPL_H__
#define __GFX_SHADER_IMPL_H__

#include <gfx/glall.h>
#include <gfx/shader.h>
#include <stdexcept>

namespace gfx{

template<shader_type T>
class shader_impl: public shader<T>{
    const std::string code_;
    GLuint handle_;

public:
    GLuint get_handle() const{
        return handle_;
    }

    shader_impl(const std::string &code):
        code_(code),
        handle_(glCreateShader(static_cast<GLenum>(T)))
    {
        const char *code_ptr = code_.c_str();

        glShaderSource(handle_, 1, &code_ptr, nullptr);
        glCompileShader(handle_);

        int params = -1;
        glGetShaderiv(handle_, GL_COMPILE_STATUS, &params);
        if (GL_TRUE != params){
            throw std::runtime_error("failed to compile shader");
        }
    }

    ~shader_impl(){
        glDeleteShader(handle_);
    }
};

}

#endif // __GFX_SHADER_IMPL_H__
