#pragma once
#ifndef __GFX_SHADER_PROGRAM_HPP__
#define __GFX_SHADER_PROGRAM_HPP__

#include <gfx/glall.hpp>
#include <gfx/shader.hpp>

#include "shader-impl.hpp"

namespace gfx{

class shader_program{
    GLuint handle_{0};
    shader_impl<shader_type::vertex> *vshdr_{nullptr};
    shader_impl<shader_type::fragment> *fshdr_{nullptr};

    bool is_linked() const{
        GLint rc = GL_FALSE;

        glGetProgramiv(handle_, GL_LINK_STATUS, &rc);

        return rc == GL_TRUE ? true : false;
    }

public:
    shader_program(): handle_(glCreateProgram()){}
    ~shader_program(){
        if (vshdr_){
            glDetachShader(handle_, vshdr_->get_handle());
        }

        if (fshdr_){
            glDetachShader(handle_, fshdr_->get_handle());
        }

        glDeleteProgram(handle_);
    }

    GLuint handle() const{
        return handle_;
    }

    void attach(shader<shader_type::vertex> *vshdr){
        if (vshdr_){
            glDetachShader(handle_, vshdr_->get_handle());
        }

        vshdr_ = dynamic_cast<shader_impl<shader_type::vertex>*>(vshdr);
        glAttachShader(handle_, vshdr_->get_handle());
    }

    void attach(shader<shader_type::fragment> *fshdr){
        if (fshdr_){
            glDetachShader(handle_, fshdr_->get_handle());
        }

        fshdr_ = dynamic_cast<shader_impl<shader_type::fragment>*>(fshdr);
        glAttachShader(handle_, fshdr_->get_handle());
    }

    void link(){
        glLinkProgram(handle_);

        glValidateProgram(handle_);

        int params = -1;
        glGetProgramiv(handle_, GL_VALIDATE_STATUS, &params);
        if (GL_TRUE != params){
            throw std::runtime_error("program is invalid");
        }
    }

    void use(){ glUseProgram(handle_); }
};

}

#endif // __GFX_SHADER_PROGRAM_HPP__
