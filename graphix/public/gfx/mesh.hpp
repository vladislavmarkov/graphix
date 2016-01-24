#pragma once
#ifndef __GFX_MESH_HPP__
#define __GFX_MESH_HPP__

#include <gfx/drawable.hpp>
#include <memory>
#include <string>

namespace gfx{

class mesh: public drawable{
public:
    static std::shared_ptr<mesh> create(const std::string &name);
};

}

#endif // __GFX_MESH_HPP__
