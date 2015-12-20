#pragma once
#ifndef __GFX_DRAWABLE_H__
#define __GFX_DRAWABLE_H__

namespace gfx{

class drawable{
public:
    virtual ~drawable() = default;
    virtual void draw() = 0;
};

}

#endif // __GFX_DRAWABLE_H__
