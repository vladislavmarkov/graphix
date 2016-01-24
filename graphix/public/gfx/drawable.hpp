#pragma once
#ifndef __GFX_DRAWABLE_HPP__
#define __GFX_DRAWABLE_HPP__

#include <string>

namespace gfx{

class drawable{
public:
    virtual ~drawable() = default;
    virtual std::string name() const = 0;
    virtual void draw() = 0;
};

}

#endif // __GFX_DRAWABLE_HPP__
