#pragma once
#ifndef __GFX_DRAWABLE_H__
#define __GFX_DRAWABLE_H__

#include <string>

namespace gfx{

class drawable{
public:
    virtual ~drawable() = default;
    virtual std::string name() const = 0;
    virtual void draw() = 0;
};

}

#endif // __GFX_DRAWABLE_H__
