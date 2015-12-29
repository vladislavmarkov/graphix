#pragma once
#ifndef __GFX_MESH_H__
#define __GFX_MESH_H__

#include <memory>
#include <string>

namespace gfx{

class mesh{
public:
    virtual ~mesh() = default;
    virtual std::string name() const = 0;
    virtual void draw() = 0;

    static std::shared_ptr<mesh> create(const std::string &name);
};

}

#endif // __GFX_MESH_H__
