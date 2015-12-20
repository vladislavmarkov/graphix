#include <gfx/camera.h>
#include <glm/glm.hpp>
#include <memory>

#include "camera_impl.h"

using std::unique_ptr;

namespace gfx{

unique_ptr<camera> camera::create(
    const glm::vec3 &position,
    const glm::vec3 &direction,
    const glm::vec3 &up_vector
){
    return unique_ptr<camera>(new camera_impl(position, direction, up_vector));
}

}
