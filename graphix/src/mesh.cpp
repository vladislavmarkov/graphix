#include <gfx/mesh.h>
#include <memory>

#include "mesh_impl.h"

using std::shared_ptr;

namespace gfx{

shared_ptr<mesh> mesh::create(const string &name){
    return shared_ptr<mesh>(new mesh_impl(name));
}

}
