#pragma once
#ifndef __GFX_MESH_H__
#define __GFX_MESH_H__

#include <gfx/drawable.h>
#include <memory>
#include <string>

namespace gfx{

class mesh: public drawable{
public:
    static std::shared_ptr<mesh> create(const std::string &name);
};

}

#endif // __GFX_MESH_H__
