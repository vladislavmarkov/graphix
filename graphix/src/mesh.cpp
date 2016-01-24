#include <gfx/mesh.hpp>
#include <memory>
#include <string>

#include "mesh-impl.hpp"

using std::shared_ptr;
using std::string;

namespace gfx{

shared_ptr<mesh> mesh::create(const string &name){
    return shared_ptr<mesh>(new mesh_impl(name));
}

}
