#include <gfx/camera.h>
#include <glm/glm.hpp>
#include <memory>

#include "camera_impl.h"

using std::shared_ptr;

namespace gfx{

shared_ptr<camera> camera::create(glm::mat4 mx){
    return shared_ptr<camera>(new camera_impl(std::move(mx)));
}

}
