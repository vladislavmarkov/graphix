#include <gfx/drawable.hpp>
#include <gfx/primitive-type.hpp>
#include <gfx/vertex-array.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "vertex-array-impl.hpp"

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
