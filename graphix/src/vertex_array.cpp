#include <gfx/drawable.h>
#include <gfx/primitive_type.h>
#include <gfx/vertex_array.h>
#include <glm/glm.hpp>
#include <vector>

#include "vertex_array_impl.h"

using std::shared_ptr;
using std::string;
using std::vector;

namespace gfx{

shared_ptr<drawable> vertex_array::create(
    const string &name,
    vector<glm::vec3> vertices,
    vector<unsigned int> indices,
    primitive_type type
){
    return shared_ptr<drawable>(
        new vertex_array_impl(name, vertices, indices, type)
    );
}

}
