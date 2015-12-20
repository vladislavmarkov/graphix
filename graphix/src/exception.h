#pragma once
#ifndef __GFX_EXCEPTION_H__
#define __GFX_EXCEPTION_H__

#include <stdexcept>

namespace gfx{

struct glew_error: std::runtime_error{
    glew_error(const std::string &msg = std::string()):
        std::runtime_error(msg)
    {}
};

struct glfw3_error: std::runtime_error{
    glfw3_error(const std::string &msg = std::string()):
        std::runtime_error(msg)
    {}
};

}

#endif // __GFX_EXCEPTION_H__
